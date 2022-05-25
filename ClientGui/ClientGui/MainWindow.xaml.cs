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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;
using System.IO;
using System.Text.Json;

namespace ClientGui
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    
    public partial class MainWindow : Window
    {
        private static Socket _clientSocket = null;



        public class loginRequest
        {
            public string username { get; set; }
            public string password { get; set; }
        }

        public MainWindow()
        {

            
            InitializeComponent();
            this.Visibility = Visibility.Hidden;


            //create a sock
            _clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            //test
            //MenuWindow.MenuHandler MenuWindow= new MenuWindow.MenuHandler();
            //MenuWindow.Show();


            //bind to the server
            ConnectToServer();

            //login handler
            if (new FileInfo("C:\\Users\\user\\Desktop\\Dolev\\magshimimProjects\\trivia_dolev_david_2022\\ClientGui\\ClientGui\\rememberme.txt").Length == 0)
            {
                loginWindow hi = new loginWindow(_clientSocket);

                //show login handler
                hi.Show();
            }
            else
            {
                string text = System.IO.File.ReadAllText("C:\\Users\\user\\Desktop\\Dolev\\magshimimProjects\\trivia_dolev_david_2022\\ClientGui\\ClientGui\\rememberme.txt");
                string _name, _password;
                string[] words = text.Split("$$$$$$$$");
                _name = words[0];
                _password = words[1];


                var login_info = new loginRequest
                {
                    username = _name,
                    password = _password
                };

                string jsonString = JsonSerializer.Serialize(login_info);
                string len = padMsg(jsonString.Length.ToString(), 4);

                string to_send = "1" + len + jsonString;

                SendInfrmaionToServer(to_send);

                string recieved = ReciveInformationFromServer();
                if (recieved[10] == '1')
                {
                    MenuWindow.MenuHandler window = new MenuWindow.MenuHandler(_clientSocket);

                    //show login handler
                    window.Show();
                }
                else
                {
                    loginWindow hi = new loginWindow(_clientSocket);
                    hi.Show();
                    hi.loginStatus.Text = "account already inside failed";
                }
            }
        }
        

        public string padMsg(string msg, int len)
        {
            while (msg.Length < len)
            {
                msg = "0" + msg;
            }
            return msg;
        }
        //connection to the server
        private void ConnectToServer()
        {
            if (!_clientSocket.Connected)
            {
                try
                {
                    _clientSocket.Connect(IPAddress.Loopback, 2022);

                }
                catch (SocketException)
                {
                    Environment.Exit(0);
                }
            }
        }
        private void SendInfrmaionToServer(string userInfo)
        {
            if (_clientSocket.Connected)
            {
                // 1 convert the form informatino to byte array
                byte[] userData = Encoding.ASCII.GetBytes(userInfo);
                // send data to the server as byte array
                _clientSocket.Send(userData);
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
                int rec = _clientSocket.Receive(reciveBuffer);
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
