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


static class Constants
{
    public const int ROOM_CLOSE = 0;
    public const int ROOM_OPEN = 1;
    public const int ROOM_ACTIVE = 2;
}


namespace ClientGui.MenuPages
{
    /// <summary>
    /// Interaction logic for AdminWaitingRoom.xaml
    /// </summary>
    public partial class AdminWaitingRoom : Window
    {
        public class roomStateResponse
        {

           public int status;
           public bool hasGameBegun;
            public List<string> players;
            public int questionCount;
            public int answerTimeout;


        }

        List<string> m_players;
        Socket mysock;
        string userName;
        int roomID = 0;

        private BackgroundWorker background_worker = new BackgroundWorker();
        public AdminWaitingRoom(Socket client, int Id, string name)
        {
            InitializeComponent();
            mysock = client;
            userName = name;
            roomID = Id;

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;
            background_worker.DoWork += getStateWorker;
            background_worker.ProgressChanged += updatePlayersListBox;
            background_worker.RunWorkerAsync();




        }

        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }

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
        private void getStateWorker(object sender, DoWorkEventArgs e)
        {
            while(true)
            {
               
                    if (background_worker.CancellationPending == false)
                    {
                        try
                        {
                            string to_send = "90000";
                            SendInfrmaionToServer(to_send);
                            string recv = ReciveInformationFromServer();
                            roomStateResponse myResponse = JsonConvert.DeserializeObject<roomStateResponse>(recv);
                            if (myResponse.status == Constants.ROOM_OPEN)
                            {
                                m_players = myResponse.players;
                                background_worker.ReportProgress(1);



                            }
                            else
                            {
                                background_worker.CancelAsync();
                            }
                            Thread.Sleep(4000);
                        }
                        catch (Exception ex)
                        {

                        }
                        

                    }
                    else
                    {
                        return;
                    }

                

                
                
            }
        }

        private void updatePlayersListBox(object sender, ProgressChangedEventArgs e)
        {
            myListBox.Items.Clear();
            foreach(string player in m_players)
            {
                myListBox.Items.Add(player);
            }
        }


        private void start_game(object sender, RoutedEventArgs e)
        {
            char command = ':';
            string to_send = command + "0000";
            SendInfrmaionToServer(to_send);
            string myResponse = ReciveInformationFromServer();

            this.Close();
            GameWindow myWindow = new GameWindow();
            myWindow.Show();


            
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
