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
using System.Windows.Threading;
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
        public class SubmitAnswerRequest
        {
            public string answerId;
        }

        public class PlayersResults
        {
            public string username;
            public int correctAnswerCount;
            public int wrongAnswerCount;
            public int averageAnswerTime;
        }
        public class GetGameResultsResponse
        {
            public int status;
            public List<PlayersResults> results = new List<PlayersResults>();

        }

        Socket mysock;
        string userName;
        private BackgroundWorker background_worker = new BackgroundWorker();
        private DispatcherTimer Timer;
        private int timeQuestion = 0;
        private int time = 0;
        private int maxQuestion = 0;
        public GameWindow(Socket socket, string user, int timePerQuestion, int _maxQuestion)
        {
            InitializeComponent();
            time = timePerQuestion;
            mysock = socket;
            userName = user;
            timeQuestion = timePerQuestion;
            txtQuestionsLeft.Text = _maxQuestion.ToString();
            Timer = new DispatcherTimer();
            Timer.Interval = new TimeSpan(0, 0, 1);
            Timer.Tick += myGame;
            Timer.Start();
            


          
            int res = getQuestion();
            
            
           
            

        }



        void myGame(object sender, EventArgs e)
        {
            if(time > 0)
            {
                time--;
                buttonTimmer.Content = time.ToString();
            }
            else
            {
                string recv = submitAnswer("X");
                int res = getQuestion();
                if(res == 0)
                {
                    txtQUESTION.Text = "Finished";
                }

                time = timeQuestion;

            }
            
        }
       
        


        private int getQuestion()
        {
            string to_send = "?0000";
            SendInfrmaionToServer(to_send);
            string reciv = ReciveInformationFromServer();
            GetQuestionResponse myQuestion = JsonConvert.DeserializeObject<GetQuestionResponse>(reciv);
            
            if (myQuestion != null && myQuestion.results.Count != 0)
            {
                txtQUESTION.Text = myQuestion.question;
                txtANSWER_BLUE.Content = myQuestion.results.ElementAt(0); // A
                txtANSWER_GREEN.Content = myQuestion.results.ElementAt(1); // B
                txtANSWER_RED.Content = myQuestion.results.ElementAt(2); // C
                txtANSWER_YELLOW.Content = myQuestion.results.ElementAt(3);//D


            }
            return myQuestion.status;
        }
        private string submitAnswer(string myAnswer)
        {
            
            var mySubmit = new SubmitAnswerRequest
            {
                answerId = myAnswer,
            };
            string jsonString = JsonConvert.SerializeObject(mySubmit);
            string len = padMsg(jsonString.Length.ToString(), 4);
            string to_send = "@" + len + jsonString;

            SendInfrmaionToServer(to_send);


            return ReciveInformationFromServer();


        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
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

        private void exit_event(object sender, RoutedEventArgs e)
        {
       
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

            
            this.Close();
            MenuWindow.MenuHandler myWindow = new MenuWindow.MenuHandler(mysock, userName);
            myWindow.Show();
        }

        private void blue_event(object sender, RoutedEventArgs e)
        {
            submitAnswer("A");
            int res = getQuestion();
            time = timeQuestion;
            if (res== 0)
            {
                txtANSWER_BLUE.Content = "Finished";
            }
        }

        private void green_event(object sender, RoutedEventArgs e)
        {
            submitAnswer("B");
            int res = getQuestion();
            time = timeQuestion;
            if (res == 0)
            {
                txtANSWER_GREEN.Content = "Finished";
            }
        }

        private void yellow_event(object sender, RoutedEventArgs e)
        {
            submitAnswer("D");
            int res = getQuestion();
            time = timeQuestion;
            if (res == 0)
            {
                txtANSWER_YELLOW.Content = "Finished";
            }
        }

        private void red_event(object sender, RoutedEventArgs e)
        {
            submitAnswer("C");
            int res = getQuestion();
            time = timeQuestion;
            if (res == 0)
            {
                txtANSWER_RED.Content = "Finished";
            }
        }
    }
}

