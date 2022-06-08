using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;
using ClientGui.MenuWindow;
//using System.Text.Json;
using Newtonsoft.Json;
using System.Threading;
using System.ComponentModel;

namespace ClientGui.MenuPages
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        Socket mysock;
        string userName;
        private List<string> roomNames = new List<string>();
        private List<RoomData> roomList = new List<RoomData>();
        private BackgroundWorker background_worker = new BackgroundWorker();

        class Parameters
        {
            public Size Size { get; set; }
            public Point Location { get; set; } 

            public Color Color { get; set; }
        }
        public class ErrorMessage
        {
            public string message;
        }
        public class joinRoomRequest
        {
           public string roomId;
        }

        public class RoomData
        {
            public int id { get; set; }
            public string name { get; set; }
            public int maxPlayers { get; set; }
            public int numberOfQuestions { get; set; }
            public int timePerQuestion { get; set; }
            public int isActive { get; set; }
        }
        public class getRoomsResponse
        {
            public List<RoomData> rooms { get; set;}
        }
        public JoinRoom(Socket client, string _name)
        {
            InitializeComponent();

            mysock = client;
            userName = _name;


            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;
            background_worker.DoWork += putNamesInListBox;
            background_worker.ProgressChanged += updateRooms;
            background_worker.RunWorkerAsync();

            
            
            
          

        }

        private void putNamesInListBox(object sender, DoWorkEventArgs e)
        {
            while(true)
            {
                if(background_worker.CancellationPending == false)
                {
                    try
                    {
                        string msg = "70000";
                        SendInfrmaionToServer(msg);

                        string response = ReciveInformationFromServer();
                        getRoomsResponse getRoomsResponse = JsonConvert.DeserializeObject<getRoomsResponse>(response);

                        //set the rooms
                        
                        //add to roomNames
                        if(getRoomsResponse.rooms != null)
                        {
                            roomList = getRoomsResponse.rooms;
                            roomNames.Clear();
                            for (var i = 0; i < getRoomsResponse.rooms.Count; i++)
                            {

                                roomNames.Add(getRoomsResponse.rooms[i].name + "#" + getRoomsResponse.rooms[i].id);
                            }
                        }    
                        
                        background_worker.ReportProgress(1);


                        Thread.Sleep(4000);
                    }
                    catch (Exception ex)
                    {
                        background_worker.CancelAsync();
                    }
                   
                }
                else
                {
                    return;
                }
                
            }
            
            
        }
        private void updateRooms(object sender, ProgressChangedEventArgs e) 
        {
            myListBox.Items.Clear();
            if(roomNames.Count > 0)
            {
                foreach (string name in roomNames)
                {
                    myListBox.Items.Add(name);
                }

            }

        }
        private void button_toggle(object sender, RoutedEventArgs e)
        {
            background_worker.CancelAsync();
            MenuHandler returnToMenu = new MenuHandler(mysock, userName);
            this.Close();
            returnToMenu.Show();
        }
        public string padMsg(string msg, int len)
        {
            while (msg.Length < len)
            {
                msg = "0" + msg;
            }
            return msg;
        }
        private void exit_toggle(object sender, RoutedEventArgs e)
        {
            this.Visibility = Visibility.Hidden;
            background_worker.CancelAsync();
            Environment.Exit(0);
        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }

        private void myListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(myListBox.SelectedItem != null)
            {
                txtSelectedRoom.Text = myListBox.SelectedItem.ToString();
                txtSelectedRoom.Visibility = Visibility.Visible;
            }    
            
        }




        private void SendInfrmaionToServer(string userInfo)
        {
            if (mysock.Connected)
            {
                // 1 convert the form informatino to byte array
                byte[] userData = Encoding.ASCII.GetBytes(userInfo);
                // send data to the server as byte array
                mysock.Send(userData);
            }
        }
        private string ReciveInformationFromServer()
        {
            try
            {

                //preper to recive data from the server
                //1.preper byte array to get all the bytes from the servr
                byte[] reciveBuffer = new byte[2048];
                //2.recive the data from the server in to the byte array and
                //return the size of bvtes how recive
                int rec = mysock.Receive(reciveBuffer);
                //3. preper byte array with the size of bytes how recive frm
                //the servr
                byte[] data = new byte[rec];
                //4. copy the byte array how reive in to the byte array with
                //the correct size
                Array.Copy(reciveBuffer, data, rec);
                //5. convert the byte array to Ascii
                string returnFormServer = Encoding.ASCII.GetString(data);
                return returnFormServer;
            }
            catch (Exception e)
            {
                //LBserverStatus.Text = "not ok";
            }
            return "";
        }
        //in case shit goes down - we can always abort to menu :)
        void abortToMenu()
        {
            MenuHandler returnToMenu = new MenuHandler(mysock, userName);
            this.Close();
            returnToMenu.Show();
        }


        //func that attemps to connect to the first avalible room
        public bool QuickJoin()
        {
            string rec;
            string msgToSend = "70000"; // ask server for room list
            SendInfrmaionToServer(msgToSend);
            string response = ReciveInformationFromServer();
            getRoomsResponse RoomsList = JsonConvert.DeserializeObject<getRoomsResponse>(response);

            if(RoomsList == null)
            {
                background_worker.CancelAsync();
                MessageBox.Show("No Rooms Available", "Alert", MessageBoxButton.OK, MessageBoxImage.Information);
                return false;
            }
            
            foreach(var v in RoomsList.rooms) // iterate through each room in roomlist
            {
                var attempJoin = new joinRoomRequest // try to connect to any room
                {
                    roomId = v.id.ToString()
                };
                rec = sendAndRecieve(attempJoin);
                if (!(rec.Contains("message"))) // if there isnt an error
                {
                    background_worker.CancelAsync();
                    WaitingRoom WaitingWindow = new WaitingRoom(mysock, userName); 
                    WaitingWindow.Show(); // connect and display waiting room
                    return true;
                }
            }
            MessageBox.Show("No Rooms Available", "Alert", MessageBoxButton.OK, MessageBoxImage.Information);
            background_worker.CancelAsync();
            return false;
        }
        //send join room request and returns rec str from server
        string sendAndRecieve(joinRoomRequest join_info)
        {
            string jsonString = JsonConvert.SerializeObject(join_info);
            string len = padMsg(jsonString.Length.ToString(), 4);

            string to_send = "5" + len + jsonString;
            SendInfrmaionToServer(to_send);
            string rec = ReciveInformationFromServer();
            return rec;
        }
        public bool joinRoomFunc(int index)
        { 

            if (index != -1) // index under 0 isnt valid
            {
                string _roomId = "";
                var join_info = new joinRoomRequest
                {
                    roomId = txtSelectedRoom.Text.Substring(index + 1) // get room id using gui
                };

                string rec = sendAndRecieve(join_info);
                if (rec.Contains("message"))
                {
                    dynamic magic = JsonConvert.DeserializeObject(rec);
                    string msg = magic["message"];
                    MessageBox.Show(msg, "Alert", MessageBoxButton.OK, MessageBoxImage.Information);
                    return false;
                }
                else
                {
                    background_worker.CancelAsync();
                    this.Close();
                    WaitingRoom WaitingWindow = new WaitingRoom(mysock, userName);
                    WaitingWindow.Show();


                    return true;
                }
            }
            return false;
        }
        private void joinRoom_toggle(object sender, RoutedEventArgs e)
        {
            int index = txtSelectedRoom.Text.LastIndexOf('#');
            joinRoomFunc(index);
        }




    }
}
