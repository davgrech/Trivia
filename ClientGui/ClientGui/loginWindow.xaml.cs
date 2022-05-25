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
using MaterialDesignThemes.Wpf;
using System.Text.Json;

using System.Net.Sockets;
using System.Net;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.IO;

namespace ClientGui
{
    /// <summary>
    /// Interaction logic for loginWindow.xaml
    /// </summary>
    public partial class loginWindow : Window, INotifyPropertyChanged
    {

        private static Socket mySock = null;
        private bool isLoggedIn = false;
        private bool isRemember = false;
        public event PropertyChangedEventHandler? PropertyChanged;
        
        public bool IsLoggedIn 
        {
            get { return isLoggedIn; } 
            set
            {
                isLoggedIn = value;
                NotifyPropertyChanged();
            }
           

        }
        
        private void NotifyPropertyChanged([CallerMemberName] String propertyName = "")
        {
            if (PropertyChanged != null)
            {
                PropertyChanged.Invoke(this, new PropertyChangedEventArgs(propertyName));   
            }
        }
        public loginWindow(Socket _clientSocket)
        {
            InitializeComponent();
            mySock = _clientSocket;
          
        }

        public bool isDarkTheme { get; set; }
        

        private readonly PaletteHelper paletteHelper = new PaletteHelper();

       



        //dark mode.
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            ITheme theme = paletteHelper.GetTheme();
            if(isDarkTheme = theme.GetBaseTheme() == BaseTheme.Dark) 
            {
                isDarkTheme = false;
                theme.SetBaseTheme(Theme.Light);
            }
            else
            {
                isDarkTheme = true;
                theme.SetBaseTheme(Theme.Dark);
            }
            paletteHelper.SetTheme(theme);
        }


        // exit button
        private void exitApp(object sender, RoutedEventArgs e)
        {
            this.Visibility = Visibility.Hidden;
            Environment.Exit(0);
        }

        //drag the window
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }


        //class of login request to json
        public class loginRequest
        {
            public string username { get; set; }
            public string password { get; set; }
        }

        public string padMsg(string msg, int len)
        {
            while(msg.Length < len)
            {
                msg = "0" + msg;
             }
            return msg;
        }
        private void toggle_login(object sender, RoutedEventArgs e)
        {

            //create a loginRequest class
            var login_info = new loginRequest
            {
                username = txtUsername.Text,
                password = txtPassowrd.Password
            };

            string jsonString = JsonSerializer.Serialize(login_info);
            string len = padMsg(jsonString.Length.ToString(), 4);

            string to_send = "1" + len + jsonString;

            SendInfrmaionToServer(to_send);


           

        }





        //connection functions
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

        //just a simulator
       
        private async void openCB(object sender, DialogOpenedEventArgs eventArgs)
        {
            try
            {
                await Task.Delay(2000);

                
               
                string recieved = ReciveInformationFromServer();
                if(recieved[10] == '1')
                {
                    if (isRemember == true)
                    {
                        File.WriteAllText("C:\\Users\\user\\Desktop\\Dolev\\magshimimProjects\\trivia_dolev_david_2022\\ClientGui\\ClientGui\\rememberme.txt", String.Empty);
                        string linetowrite = txtUsername.Text + "\n" + txtPassowrd.Password;
                        await File.WriteAllTextAsync("C:\\Users\\user\\Desktop\\Dolev\\magshimimProjects\\trivia_dolev_david_2022\\ClientGui\\ClientGui\\rememberme.txt", linetowrite);

                    }
                    else
                    {
                        //var fileStream = File.Open("C:\\Users\\user\\Desktop\\Dolev\\magshimimProjects\\trivia_dolev_david_2022\\ClientGui\\ClientGui\\rememberme.txt", FileMode.Open);
                        //File.WriteAllText("C:\\Users\\user\\Desktop\\Dolev\\magshimimProjects\\trivia_dolev_david_2022\\ClientGui\\ClientGui\\rememberme.txt", String.Empty);
                    }
                    isLoggedIn = true;
                    eventArgs.Session.Close(true);
                    MenuWindow.MenuHandler moveToMenu = new MenuWindow.MenuHandler(mySock);
                    this.Close();
                    moveToMenu.Show();
                }
                else
                {
                    isLoggedIn = false;
                    eventArgs.Session.Close(false);

                }
                
            }
            catch
            {

            }
        }

     

        private void closingCB(object sender, DialogClosingEventArgs eventArgs)
        {
            
            if(eventArgs.Parameter != null)
            {
                if (((bool)eventArgs.Parameter) == true)
                {
                    //login Success
                    IsLoggedIn = true;

                    loginStatus.Text = "Login Succeed";
                    loginStatus.Visibility = Visibility.Visible;
                    this.Visibility = Visibility.Hidden;
                    MenuWindow.MenuHandler menuWindow = new MenuWindow.MenuHandler(mySock);
                    menuWindow.Show();


                }
                else if (((bool)eventArgs.Parameter) == false)
                {
                    //login Failed
                    IsLoggedIn = false;

                    loginStatus.Text = "Login Failed";
                    loginStatus.Visibility = Visibility.Visible;
                }
            }
           
        }
        /*
         * onclikc func that redirects user to sign up page
         */
        private void signupBtn_Click(object sender, RoutedEventArgs e)
        {
            SignUp newSignup = new SignUp(mySock);
            newSignup.Show();
            this.Close();
        }

        private void toggle_remember(object sender, RoutedEventArgs e)
        {
            isRemember = (bool)Remember.IsChecked;
        }
    }
}
