﻿using System;
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

using MaterialDesignThemes.Wpf;

using Newtonsoft.Json;
using System.Net.Sockets;
using System.Net;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.IO;



using System.Threading;
namespace ClientGui
{
    /// <summary>
    /// Interaction logic for waitingForResults.xaml
    /// </summary>
    public partial class waitingForResults : Window
    {
        public class gameResults
        {
            public int status;
            public List<PlayerResults> results;
        }
        public class PlayerResults
        {
            public string username;
            public int correctAnswerCount;
            public int wrongAnswerCount;
            public int averageAnswerTime;
        }

        private static Socket mySock = null;
        private BackgroundWorker background_worker = new BackgroundWorker();
        public waitingForResults(Socket userSock, string user)
        {
            InitializeComponent();
            mySock = userSock;

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;
            background_worker.DoWork += waitForGameToFinish;
            background_worker.ProgressChanged += DisplayAllElements;
            background_worker.RunWorkerAsync();








         
            







        }
        private void waitForGameToFinish(object sender, DoWorkEventArgs e)
        {
            string msg_to_send = "A0000";

            SendInfrmaionToServer(msg_to_send);

            string reciv = ReciveInformationFromServer();
            gameResults myGameResult = JsonConvert.DeserializeObject<gameResults>(reciv);
            if (myGameResult != null)
            {
                while (myGameResult.status != 1)
                {
                    SendInfrmaionToServer(msg_to_send);

                    reciv = ReciveInformationFromServer();
                    myGameResult = JsonConvert.DeserializeObject<gameResults>(reciv);


                    Thread.Sleep(1000);
                }

                //display the results on screen
                background_worker.ReportProgress(1);
                background_worker.CancelAsync();


            }
        }
        private void DisplayAllElements(object sender, ProgressChangedEventArgs e)
        {
            Waiting.Visibility = Visibility.Hidden;
            Star1.Visibility = Visibility.Visible;
            Star2.Visibility = Visibility.Visible;
            Star3.Visibility = Visibility.Visible;

            First.Visibility = Visibility.Visible;
            Second.Visibility = Visibility.Visible;
            Third.Visibility = Visibility.Visible;

            Place.Visibility = Visibility.Visible;
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
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
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


    }
}
