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



namespace ClientGui.MenuPages
{
    /// <summary>
    /// Interaction logic for WaitingRoom.xaml
    /// </summary>
    public partial class WaitingRoom : Window
    {

        int isClose = 1;
        Socket mysock;
        string userName;
        int timeperquestion = 0;
        List<string> m_players;
        int maxQuestions = 0;
        public class roomStateResponse
        {

            public int status;
            public bool hasGameBegun;
            public List<string> players;
            public int questionCount;
            public int answerTimeout;


        }

        private BackgroundWorker background_worker = new BackgroundWorker();


        public WaitingRoom(Socket _mysock, string _userName, int secondsPerQustion, int _maxQuestions)
        {
            InitializeComponent();
            mysock = _mysock;
            userName = _userName;
            timeperquestion = secondsPerQustion;
            maxQuestions = _maxQuestions;

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;
            background_worker.DoWork += getStateWorker;
            background_worker.ProgressChanged += updatePlayersListBox;
            background_worker.RunWorkerCompleted += back_worker_do_work;
            background_worker.RunWorkerAsync();


        }
        void back_worker_do_work(object sender, RunWorkerCompletedEventArgs e)
        {
            this.Close();
        }
        private void getStateWorker(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if(background_worker.CancellationPending == false)
                {
                    string to_send = "90000";
                    SendInfrmaionToServer(to_send);
                    string recv = ReciveInformationFromServer();
                    roomStateResponse myResponse = JsonConvert.DeserializeObject<roomStateResponse>(recv);
                    if (myResponse.status == Constants.ROOM_OPEN)
                    {
                        m_players = myResponse.players;
                        background_worker.ReportProgress(1);
                        isClose = 1;


                    }
                    else if (myResponse.status == Constants.ROOM_CLOSE)
                    {

                        sendLeaveCommandToServer(mysock);
                        ReciveInformationFromServer();
                        background_worker.CancelAsync();
                        isClose = 0;
                        background_worker.ReportProgress(1);
                        
                        
                    }
                    else if (myResponse.status == Constants.ROOM_ACTIVE)
                    {
                        isClose = 2;
                        background_worker.CancelAsync();
                        background_worker.ReportProgress(1);
                      


                    }
                    Thread.Sleep(4000);
                }
                else
                {
                    return;
                }
                
            }
        }


        private void updatePlayersListBox(object sender, ProgressChangedEventArgs e)
        {
            if(isClose == 1)
            {
                myListBox.Items.Clear();
                foreach (string player in m_players)
                {
                    myListBox.Items.Add(player);
                }
            }
            else if(isClose == 0)
            {

                this.Close();
                MenuWindow.MenuHandler window = new MenuWindow.MenuHandler(mysock, userName);
                window.Show();
            }
            else if(isClose == 2)
            {
                GameWindow myWindow = new GameWindow(mysock, userName, timeperquestion, maxQuestions);
                this.Close();
                myWindow.Show();
            }
            
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
        void sendLeaveCommandToServer(Socket client)
        {
            char command = '8';
            string to_send = command + "0000";
            SendInfrmaionToServer(to_send);
        }
        private void return_toggle(object sender, RoutedEventArgs e)
        {
            //return to menu // leave room
            sendLeaveCommandToServer(mysock);
            ReciveInformationFromServer();
            background_worker.CancelAsync();
            this.Close();
            MenuWindow.MenuHandler window = new MenuWindow.MenuHandler(mysock, userName);
            window.Show();


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
