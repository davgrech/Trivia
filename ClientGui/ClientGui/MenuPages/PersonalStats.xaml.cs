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
    /// Interaction logic for PersonalStats.xaml
    /// </summary>
    public class recvInfo
    {
        public string PersonalScore { get; set; }


    }

    public class Statistics
    {
        public string NAME { get; set; }
        public string CORRECT_ANSWERS { get; set; }
        public string TOTAL_ANSWERS { get; set; }
        public string GAMES { get; set; }
        public string AVG_TIME { get; set; }
        public string WINNER_POINTS { get; set; }
    }

    public partial class PersonalStats : Window
    {
        private static Socket mysock = null;
        private string user;
       //init func
        public PersonalStats(Socket _sock, string username)
        {
            InitializeComponent();
            mysock = _sock;
            user = username;
            recvInfo infoRecv = getUserStats(username);
            Statistics userStats = parseJibbrish(infoRecv.PersonalScore);
            loadTextToWindow(userStats);




        }
        //load stats to window 
        void loadTextToWindow(Statistics userStats)
        {
            userTxt.Text = userStats.NAME + "'s Personal Stats";
            firstDisplay.Text = userStats.NAME + " Has A Total Of " + userStats.GAMES + " Games ";
            secondDisplay.Text = userStats.NAME + " Has Answerd " + userStats.TOTAL_ANSWERS + " Questions\n Of Which He Got " +
                userStats.CORRECT_ANSWERS + " Answers Correct";
            ThirdDisplay.Text = userStats.NAME + "'s Avarage Playtime is: " + userStats.AVG_TIME + " Hours\n" +
                userStats.NAME + " Has Scored A Total Of: " + userStats.WINNER_POINTS + " Winner Points";
        }
        //parse the unsorted data sent by server using spilts and return a statistics object with all of it
        public Statistics parseJibbrish(string str)
        {
            string[] words = str.Split(",");
            string name = words[0].Split(": ")[1];
            string correctAns = words[1].Split(": ")[1];
            string totalAns = words[1].Split(": ")[1];
            string games = words[1].Split(": ")[1];
            string avgTime = words[1].Split(": ")[1];
            string winnerPts = words[1].Split(": ")[1];
            var UserStats = new Statistics
            {
                NAME = name,
                CORRECT_ANSWERS = correctAns,
                TOTAL_ANSWERS = totalAns,
                GAMES = games,
                AVG_TIME = avgTime,
                WINNER_POINTS = winnerPts

            };
            return UserStats;
        }
        //ask server for user stats - func gets it and Deserializes it
        private recvInfo getUserStats(string uname)
        {
            string jsonString = JsonSerializer.Serialize(uname);
            string len = padMsg(jsonString.Length.ToString(), 4);
            string to_send = "<" + len + jsonString;
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
        public string padMsg(string msg, int len)
        {
            while (msg.Length < len)
            {
                msg = "0" + msg;
            }
            return msg;
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

    }
}
