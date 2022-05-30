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
using MaterialDesignThemes.Wpf;
using System.IO;
using System.Media;
using ClientGui.MenuPages;

namespace ClientGui.MenuWindow
{
    /// <summary>
    /// Interaction logic for MenuHandler.xaml
    /// </summary>
    /// 
   
    public partial class MenuHandler : Window
    {

        string userName;
        private static Socket mySock = null;

        public MenuHandler(Socket _clientSocket, string user)
        {
            InitializeComponent();
            mySock = _clientSocket;
            userName = user;
            userTxt.Text = "hi "+user+"!";
            //playSound();



        }
        private void playSound()
        {
            SoundPlayer soundPlayer = new SoundPlayer("\\Resources\\menuMusic.wav"); 
            soundPlayer.Play();
            soundPlayer.PlayLooping();


        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            try
            {
                DragMove();
            }
            catch (Exception ex)
            {
                //lol
            }
        }

        private void logout_toggle(object sender, RoutedEventArgs e)
        {
            string msgToSend = "20000";
            SendInfrmaionToServer(msgToSend);
            string received = ReciveInformationFromServer();
            if(received[10] == '1')
            {
                File.WriteAllText("rememberme.txt", String.Empty);
                this.Close();
                loginWindow loginHandle = new loginWindow(mySock);
                loginHandle.Show();
            }

        }

        private void exit_toggle(object sender, RoutedEventArgs e)
        {
            this.Visibility = Visibility.Hidden;
            Environment.Exit(0);
        }




        private void SendInfrmaionToServer(string userInfo)
        {
            if (mySock.Connected)
            {
                // 1 convert the form informatino to byte array
                byte[] userData = Encoding.ASCII.GetBytes(userInfo);
                // send data to the server as byte array
                mySock.Send(userData);
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
                int rec = mySock.Receive(reciveBuffer);
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


        //create room
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            CreateRoom moveToCreateRoom = new CreateRoom(mySock, userName);
            moveToCreateRoom.Show();
            this.Close();
        }


        //join room 
        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            JoinRoom moveToJoinRoom = new JoinRoom(mySock, userName);
            moveToJoinRoom.Show();
            this.Close();

        }
        /*
         * personal stats
         */
        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            
            PersonalStats moveToStats = new PersonalStats(mySock, userName);
            moveToStats.Show();
            this.Close();
            
        }

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {
            HighScores moveToLeader = new HighScores(mySock, userName);
            moveToLeader.Show();
            this.Close();
            
        }
        //quick room join
        
        private void Button_Click_5(object sender, RoutedEventArgs e)
        {
            
            JoinRoom joinRoom = new JoinRoom(mySock, userName);
            joinRoom.joinRoom(0, true); // join room indexed at 0
            this.Close();
        }
        //quick room creation
        // makes a room with stats i gave it yolo
        private void Button_Click_6(object sender, RoutedEventArgs e)
        {
            CreateRoom quickCreate = new CreateRoom(mySock, userName);
            System.Random random = new System.Random();
            string createInfo = "{\"roomName\":\"" + "Room " + (random.Next(1, 50)).ToString() + "\",\"maxUsers\":\"" + ((5).ToString()) + "\",\"questionCount\":\"" + ((12).ToString()) + "\",\"answerTimeout\":\"" + ((10).ToString()) + "\"}";
            quickCreate.CreateNewRoom(createInfo, true);
            this.Close();
        }
    }





}
