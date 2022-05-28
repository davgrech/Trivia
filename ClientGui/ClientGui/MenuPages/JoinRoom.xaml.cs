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
using System.Text.Json;
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


        public class joinRoomRequest
        {
            int roomId;
        }
        public JoinRoom(Socket client, string userName)
        {
            InitializeComponent();

            mysock = client;
            name = userName;


            string[] x = { "hi", "my", "name", "is", "david" };
            string getStringToParse = getRooms();
            
            
            
            myListBox.ItemsSource = x;

        }
       
       private string getRooms()
        {
            string msg = "70000";
            SendInfrmaionToServer(msg);
            string response = ReciveInformationFromServer();
            dynamic magic = JsonConvert.DeserializeObject(response);
            return magic["Rooms"];
        }
        private void button_toggle(object sender, RoutedEventArgs e)
        {
            MenuHandler returnToMenu = new MenuHandler(mysock, name);
            this.Close();
            returnToMenu.Show();
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



    }
}
