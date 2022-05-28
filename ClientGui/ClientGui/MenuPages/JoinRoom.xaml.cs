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


namespace ClientGui.MenuPages
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        Socket mysock;
        string name;
        private List<string> roomNames = new List<string>();
        private List<RoomData> roomList = new List<RoomData>();


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
        public JoinRoom(Socket client, string userName)
        {
            InitializeComponent();

            mysock = client;
            name = userName;


            
            putNamesInListBox();
            
            
            
          

        }
       private void putNamesInListBox()
        {
            string msg = "70000";
            SendInfrmaionToServer(msg);
            string response = ReciveInformationFromServer();
            getRoomsResponse getRoomsResponse = JsonConvert.DeserializeObject<getRoomsResponse>(response);

            //set the rooms
            roomList = getRoomsResponse.rooms;

            //add to roomNames
            for(var i = 0; i < getRoomsResponse.rooms.Count; i++)
            {
                roomNames.Add(getRoomsResponse.rooms[i].name);
            }
            myListBox.ItemsSource = roomNames;
            
        }
        private void button_toggle(object sender, RoutedEventArgs e)
        {
            MenuHandler returnToMenu = new MenuHandler(mysock, name);
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

        private void joinRoom_toggle(object sender, RoutedEventArgs e)
        {
            for(var i = 0; i < roomList.Count;i++)
            {
                if(roomList[i].name == txtSelectedRoom.Text)
                {
                    var join_info = new joinRoomRequest
                    {
                        roomId = roomList[i].id.ToString()
                    };
                    string jsonString = JsonConvert.SerializeObject(join_info);
                    string len = padMsg(jsonString.Length.ToString(), 4);

                    string to_send = "5" + len + jsonString;
                    SendInfrmaionToServer(to_send);
                    string rec = ReciveInformationFromServer();
                    if(rec[10] != '1')
                    {
                        dynamic magic = JsonConvert.DeserializeObject(rec);
                        txtSelectedRoom.Text = magic["message"];
                        txtSelectedRoom.Visibility = Visibility.Visible;
                    }
                    else
                    {
                        txtSelectedRoom.Text = "succeed to join";
                        txtSelectedRoom.Visibility = Visibility.Visible;
                    }
                    



                }
            }
        }
    }
}
