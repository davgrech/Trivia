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
            public string correct;
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
        private DispatcherTimer suspend;
        private int timeQuestion = 0;
        private int time = 0;
        private int time_of_suspend = 0;
        private int maxQuestion = 0;
        int howmuchQuestionsLeft = 0;
        private GetQuestionResponse currentQuestion = null;
        private DispatcherTimer _time = null;
        public GameWindow(Socket socket, string user, int timePerQuestion, int _maxQuestion)
        {
            InitializeComponent();
            time = timePerQuestion;
            mysock = socket;
            userName = user;
            timeQuestion = timePerQuestion;
            txtQuestionsLeft.Text = _maxQuestion.ToString();
            howmuchQuestionsLeft = _maxQuestion;
            _time = new DispatcherTimer {};
            _time.Interval = new TimeSpan(0, 0, 1);
            _time.Tick += myGame;
            _time.Start();
           

            suspend = new DispatcherTimer {};
            suspend.Interval = new TimeSpan(0, 0, 1);
            suspend.Tick += mySuspend;
            time_of_suspend = 5;

          
            int res = getQuestion();
            
            
           
            

        }
        void mySuspend(object sender, EventArgs e)
        {
            if(time_of_suspend > 0)
            {
                time_of_suspend--;
                buttonTimmerSuspend.Content = time_of_suspend.ToString();
            }
            else
            {
                getQuestion();
                suspend.Stop();
                buttonTimmerSuspend.Visibility = Visibility.Hidden;
            }
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
               

                time = timeQuestion;
               
            }
            
        }
       
        


        private int getQuestion()
        {
            Next.Visibility = Visibility.Hidden;
            buttonTimmerSuspend.Visibility = Visibility.Hidden;
            StarR.Visibility = Visibility.Hidden;
            StarG.Visibility = Visibility.Hidden;
            StarB.Visibility = Visibility.Hidden;
            StarY.Visibility = Visibility.Hidden;

            time_of_suspend = 10;
            time = timeQuestion;
            _time.Start();
            suspend.Stop();
            string to_send = "?0000";
            SendInfrmaionToServer(to_send);
            string reciv = ReciveInformationFromServer();
            GetQuestionResponse myQuestion = JsonConvert.DeserializeObject<GetQuestionResponse>(reciv);
            currentQuestion = myQuestion;

            if (myQuestion != null && myQuestion.results.Count != 0)
            {
                txtQUESTION.Text = myQuestion.question;
                txtANSWER_BLUE.Content = myQuestion.results.ElementAt(0); // A
                txtANSWER_GREEN.Content = myQuestion.results.ElementAt(1); // B
                txtANSWER_RED.Content = myQuestion.results.ElementAt(2); // C
                txtANSWER_YELLOW.Content = myQuestion.results.ElementAt(3);//D

                howmuchQuestionsLeft--;
                txtQuestionsLeft.Text = howmuchQuestionsLeft.ToString();


            }
            if(currentQuestion != null)
            {
                if (myQuestion.question == "")
                {
                    
                    _time.Stop();
                    suspend.Stop();
                    waitingForResults window = new waitingForResults(mysock, userName);
                    this.Close();

                    window.Show();

                }
            }
            
           
        
            return myQuestion.status;
        }
        private string submitAnswer(string myAnswer)
        {

            Next.Visibility = Visibility.Visible;
            buttonTimmerSuspend.Visibility = Visibility.Visible;

            var mySubmit = new SubmitAnswerRequest
            {
                answerId = myAnswer,
            };
            string jsonString = JsonConvert.SerializeObject(mySubmit);
            string len = padMsg(jsonString.Length.ToString(), 4);
            string to_send = "@" + len + jsonString;

            SendInfrmaionToServer(to_send);
            string reciv = ReciveInformationFromServer();
            dynamic magic = JsonConvert.DeserializeObject(reciv);
            if (magic["status"] == 1)
            {

                string correct = txtCorrect.Text;
               
                int x = Int32.Parse(correct.Substring(17)) + 1;
                txtCorrect.Text ="correct Answers: " + x.ToString();
            }


            if ((string)txtANSWER_BLUE.Content == currentQuestion.correct)
            {
                StarB.Visibility = Visibility.Visible;


            }

            else if ((string)txtANSWER_GREEN.Content == currentQuestion.correct)
            {
                StarG.Visibility = Visibility.Visible;



            }

            else if ((string)txtANSWER_RED.Content == currentQuestion.correct)
            {
                StarR.Visibility = Visibility.Visible;


            }
            else if ((string)txtANSWER_YELLOW.Content == currentQuestion.correct)
            {
                StarY.Visibility = Visibility.Visible;


            }
           
            suspend.Start();
            _time.Stop();
            buttonTimmerSuspend.Visibility = Visibility.Visible;




            return reciv;


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
            if(_time.IsEnabled == true)
            {
                submitAnswer("A");
            }
            
          
            
        }

        private void green_event(object sender, RoutedEventArgs e)
        {
            if (_time.IsEnabled == true)
            {
                submitAnswer("B");
            }
            
        }

        private void yellow_event(object sender, RoutedEventArgs e)
        {
            if (_time.IsEnabled == true)
            {
                submitAnswer("D");
            }
           
        }

        private void red_event(object sender, RoutedEventArgs e)
        {
            if (_time.IsEnabled == true)
            {
                submitAnswer("C");
            }
           
        }




        private void nexttQuestion(object sender, RoutedEventArgs e)
        {
            int res = getQuestion();

        }       
    }
}

