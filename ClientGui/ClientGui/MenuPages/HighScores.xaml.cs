using ClientGui.MenuWindow;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace ClientGui.MenuPages
{
    /// <summary>
    /// Interaction logic for HighScores.xaml
    /// </summary>
    /// 
    class recvInfoLeaderboard
    {

    }
    public partial class HighScores : Window
    {
        private static Socket mysock = null;
        string user;
        class recvLeaderboard
        {

        }
        public HighScores(Socket _sock, string _uname)
        {
            InitializeComponent();

            mysock = _sock;
            user= _uname;
            getUserStats();
        }
        



        //ask server for user stats - func gets it and Deserializes it
        private recvInfo getUserStats()
        {

            string to_send = "90000";
            SendInfrmaionToServer(to_send);
            string received = ReciveInformationFromServer();
            try
            {
                recvInfo? getstats = JsonSerializer.Deserialize<recvInfo>(received);
                return getstats;
            }
            catch (Exception ex)
            {
                return null;
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

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            MenuHandler returnToMenu = new MenuHandler(mysock, user);
            this.Close();
            returnToMenu.Show();
        }

        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }
        private void exit_toggle(object sender, RoutedEventArgs e)
        {
            this.Visibility = Visibility.Hidden;
            Environment.Exit(0);
        }

    }
}



