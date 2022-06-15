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
using System.Net;
using System.Net.Sockets;

using Newtonsoft.Json;
using System.Threading;
using System.ComponentModel;
namespace ClientGui
{
    /// <summary>
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {


        class GetQuestionResponse
        {
            // private List<string> roomNames = new List<string>();
            public int status;
            public string question;
            public List<string> results = new List<string>();
        }

        Socket mysock;
        string userName;
        private BackgroundWorker background_worker = new BackgroundWorker();
        public GameWindow(Socket socket, string user)
        {
            InitializeComponent();

            mysock = socket;
            userName = user;

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;
            // put function -> do work ->background_worker.DoWork += getStateWorker;
            // put function here where we can change -> background_worker.ProgressChanged += updatePlayersListBox;
            background_worker.RunWorkerAsync();

            // getRoomsResponse getRoomsResponse = JsonConvert.DeserializeObject<getRoomsResponse>(response);
            string to_send = "?0000";
            SendInfrmaionToServer(to_send);
            string reciv = ReciveInformationFromServer();
            GetQuestionResponse myQuestion = JsonConvert.DeserializeObject<GetQuestionResponse>(reciv);
            if(myQuestion != null)
            {
                txtQUESTION.Text = myQuestion.question;
                txtANSWER_BLUE.Content = myQuestion.results.ElementAt(0);
                txtANSWER_GREEN.Content = myQuestion.results.ElementAt(1);
                txtANSWER_RED.Content = myQuestion.results.ElementAt(2);
                txtANSWER_YELLOW.Content = myQuestion.results.ElementAt(3);


            }






        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }
        /*
         private void exit_toggle(object sender, RoutedEventArgs e)
        {
            background_worker.CancelAsync();
            this.Visibility = Visibility.Hidden;
            Environment.Exit(0);
        }

        private void return_toggle(object sender, RoutedEventArgs e)
        {
            //return to menu // close room
            char command = ';';
            string to_send = command + "0000";
            SendInfrmaionToServer(to_send);

            string msg = ReciveInformationFromServer();

            background_worker.CancelAsync();
            this.Close();
            MenuWindow.MenuHandler myWindow = new MenuWindow.MenuHandler(mysock, userName);
            myWindow.Show();

        }
         */






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

        private void exit_event(object sender, RoutedEventArgs e)
        {
            background_worker.CancelAsync();
            this.Visibility = Visibility.Hidden;
            Environment.Exit(0);
        }

        private void giveup_event(object sender, RoutedEventArgs e)
        {
            //return to menu // close room
            char command = '>';
            string to_send = command + "0000";
            SendInfrmaionToServer(to_send);

            string msg = ReciveInformationFromServer();

            background_worker.CancelAsync();
            this.Close();
            MenuWindow.MenuHandler myWindow = new MenuWindow.MenuHandler(mysock, userName);
            myWindow.Show();
        }
    }
}

