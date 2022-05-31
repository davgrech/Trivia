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
        public string HighScores { get; set; }
    }
    public class topThree
    {
        public string firstName { get; set; }
        public string firstPoints { get; set; }
        public string SecondName { get; set; }
        public string SecondPoints { get; set; }
        public string ThirdName { get; set; }
        public string thirdPoints { get; set; }

    }
    public partial class HighScores : Window
    {
        private static Socket mysock = null;
        string user;

        public HighScores(Socket _sock, string _uname)
        {
            InitializeComponent();

            mysock = _sock;
            user= _uname;
            recvInfoLeaderboard data = getUserStats();
            topThree leaders = ParseToTop(data.HighScores);
            setText(leaders);
        }
        void setText(topThree leaders)
        {
            firstDisplay.Text = "First Place\n" + leaders.firstName + "\n With " + leaders.firstPoints + " Winner Points";
            secondDisplay.Text = "Second Place\n" + leaders.SecondName + "\n With " + leaders.SecondPoints + " Winner Points";
            ThirdDisplay.Text = "Third Place\n" + leaders.ThirdName + "\n With " + leaders.thirdPoints + " Winner Points";
        }



        //ask server for user stats - func gets it and Deserializes it
        private recvInfoLeaderboard getUserStats()
        {

            string to_send = "=0000";
            SendInfrmaionToServer(to_send);
            string received = ReciveInformationFromServer();
            try
            {
                recvInfoLeaderboard? getLeader = JsonSerializer.Deserialize<recvInfoLeaderboard>(received);
                return getLeader;
            }
            catch (Exception ex)
            {
                return null;
            }
        }


        public topThree ParseToTop(string str)
        {
            string[] words = str.Split(",");
            var newThree = new topThree()
            {
                firstName = words[0].Split(":")[0],
                firstPoints = words[0].Split(":")[1],
                SecondName = words[1].Split(":")[0],
                SecondPoints = words[1].Split(":")[1],
                ThirdName = words[2].Split(":")[0],
                thirdPoints = words[2].Split(":")[1]
            };
            return newThree;

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



