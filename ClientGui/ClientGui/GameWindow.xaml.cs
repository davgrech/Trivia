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
            
            string to_send = "?0000";
            SendInfrmaionToServer(to_send);
            string reciv = ReciveInformationFromServer();




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

