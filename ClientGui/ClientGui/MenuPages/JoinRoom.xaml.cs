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
            public int id;
            public string name;
            public int maxPlayers;
            public int numberOfQuestions;
            public int timePerQuestion;
            public int isActive;
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
                string msg = "70000";
                SendInfrmaionToServer(msg);
               
                string response = ReciveInformationFromServer();
                getRoomsResponse getRoomsResponse = JsonConvert.DeserializeObject<getRoomsResponse>(response);

                //set the rooms
                roomList = getRoomsResponse.rooms;
                roomNames.Clear();
                //add to roomNames
                for (var i = 0; i < getRoomsResponse.rooms.Count; i++)
                {

                    roomNames.Add(getRoomsResponse.rooms[i].name + "#" + getRoomsResponse.rooms[i].id);
                }
                background_worker.ReportProgress(1);
                

                Thread.Sleep(4000);
            }
            
            
        }
        private void updateRooms(object sender, ProgressChangedEventArgs e) 
        {
            myListBox.Items.Clear();
            
            foreach(string name in roomNames)
            {
                myListBox.Items.Add(name);
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
            txtSelectedRoom.Text = myListBox.SelectedItem.ToString();
            txtSelectedRoom.Visibility = Visibility.Visible;

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
        string ParseToID(string str)
        {
            if (!(System.Text.RegularExpressions.Regex.IsMatch(str, @"^[a-zA-Z]+$"))) // if str doesnt contain any letter
            {
                return "";
            }
            str = (str.Split("\\"))[4];
            str = str.Remove(0, 2);
            return str.Remove(str.Length - 1);

        }
        //func that returns the room id (a "non gui" way to get the room id)
        string GetRoomID(int index)
        {
            string msgToSend = "70000";
            SendInfrmaionToServer(msgToSend);
            string received = ReciveInformationFromServer();
            return ParseToID(received);
        }
        public void joinRoomFunc(int index, bool IsQuickCreate)
        {
            string _roomId;
            if (index != -1)
            {
                var join_info = new joinRoomRequest
                {
                    roomId = txtSelectedRoom.Text.Substring(index + 1)
                };
                if (IsQuickCreate)
                {
                    _roomId = GetRoomID(index);
                    if(String.IsNullOrEmpty(_roomId))
                    {
                        MessageBox.Show("No Rooms Available", "Alert", MessageBoxButton.OK, MessageBoxImage.Information);
                        return;

                    }
                    join_info.roomId = _roomId;
                }


                

                string jsonString = JsonConvert.SerializeObject(join_info);
                string len = padMsg(jsonString.Length.ToString(), 4);

                string to_send = "5" + len + jsonString;
                SendInfrmaionToServer(to_send);
                string rec = ReciveInformationFromServer();

                if (rec.Contains("message"))
                {
                    dynamic magic = JsonConvert.DeserializeObject(rec);
                    string msg = magic["message"];
                    MessageBox.Show(msg, "Alert", MessageBoxButton.OK, MessageBoxImage.Information);

                }
                else
                {

                    WaitingRoom WaitingWindow = new WaitingRoom(mysock, int.Parse(txtSelectedRoom.Text.Substring(index + 1)), userName);
                    if(!IsQuickCreate) // if not quick create theres nothig to close
                    {
                       this.Close();
                    }
                   
                    WaitingWindow.Show();


                }
            }
        }
        public void joinRoom_toggle(object sender, RoutedEventArgs e)
        {
            int index = txtSelectedRoom.Text.LastIndexOf('#');
            joinRoomFunc(index, false);


        }




    }
}
