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
using System.Net.Sockets;
using System.Net;
using ClientGui.MenuWindow;
using System.Text.Json;
using Newtonsoft.Json;
namespace ClientGui.MenuPages
{

    public partial class CreateRoom : Window
    {
        private Socket mySock;
        private string user;
        public CreateRoom(Socket client, string userName)
        {

            mySock = client;
            user = userName;
            InitializeComponent();

        }

        private void button_toggle(object sender, RoutedEventArgs e)
        {
            MenuHandler returnToMenu = new MenuHandler(mySock, user);
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
        //func that creates a room using Create info
        public void CreateNewRoom(string createInfo, bool isQuickCreate)
        {

            string msgLen = padMsg(createInfo.Length.ToString(), 4);
            string to_send = "4" + msgLen + createInfo;

            SendInfrmaionToServer(to_send);

            string response = ReciveInformationFromServer();
            if (!(response.Contains("message")))
            {
                if (!isQuickCreate) // if isnt quick create mode theres no need to close a window
                {
                    this.Close();
                }
                dynamic magic = JsonConvert.DeserializeObject(response);
                string stringID = magic["Id"];
                int id = Int16.Parse(stringID);
                dynamic results = JsonConvert.DeserializeObject(createInfo);
                int x = results["answerTimeout"];
                int y = results["questionCount"];
                if(isQuickCreate)
                {
                  
                    AdminWaitingRoom waitingWindow = new AdminWaitingRoom(mySock, id, user, x,y);
                    waitingWindow.Show();
                }
                else
                {
                    
                    AdminWaitingRoom waitingWindow = new AdminWaitingRoom(mySock, id, user, Int32.Parse(txtQuestionTimeout.Text), Int32.Parse(txtMaxQuestions.Text));
                    waitingWindow.Show();
                }
                
               
            }
            else
            {
                dynamic magic = JsonConvert.DeserializeObject(response);
                string msg = magic["message"];
                MessageBox.Show(msg, "Alert", MessageBoxButton.OK, MessageBoxImage.Information);
            }
        }
        //create room using input from CreateRoomxaml
        private void createRoom_btn(object sender, RoutedEventArgs e)
        {
            string createInfo = "{\"roomName\":\"" + txtRoomName.Text + "\",\"maxUsers\":\"" + txtMaxPlayers.Text + "\",\"questionCount\":\"" + txtMaxQuestions.Text + "\",\"answerTimeout\":\"" + txtQuestionTimeout.Text + "\"}";
            CreateNewRoom(createInfo, false);




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
