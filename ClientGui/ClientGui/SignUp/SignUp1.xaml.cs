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

namespace ClientGui
{
    /// <summary>
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUp : Window, INotifyPropertyChanged
    {

        private static Socket mySock = null;
        private bool isSignedUp = false;

        public event PropertyChangedEventHandler? PropertyChanged;

        public bool IsLoggedIn
        {
            get { return isSignedUp; }
            set
            {
                isSignedUp = value;
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
        public SignUp(Socket _clientSocket)
        {
            InitializeComponent();
            mySock = _clientSocket;
        }
        public bool isDarkTheme { get; set; }


        private readonly PaletteHelper paletteHelper = new PaletteHelper();
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            ITheme theme = paletteHelper.GetTheme();
            if (isDarkTheme = theme.GetBaseTheme() == BaseTheme.Dark)
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
                if (recieved[10] == '0')
                {
                    isSignedUp = true;
                    eventArgs.Session.Close(true);
                }
                else
                {
                    isSignedUp = false;
                    eventArgs.Session.Close(false);

                }

            }
            catch
            {

            }
        }



        private void closingCB(object sender, DialogClosingEventArgs eventArgs)
        {

            if (eventArgs.Parameter != null)
            {
                if (((bool)eventArgs.Parameter) == true)
                {
                    //login Success
                    IsLoggedIn = true;

                    SignUpStatus.Text = "Signed up successfully";
                    SignUpStatus.Visibility = Visibility.Visible;
                }
                else if (((bool)eventArgs.Parameter) == false)
                {
                    //login Failed
                    IsLoggedIn = false;

                    SignUpStatus.Text = "Sign up Failed";
                    SignUpStatus.Visibility = Visibility.Visible;
                }
            }

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


        public class SignUpRequest
        {
            public string username { get; set; }
            public string password { get; set; }
            public string email { get; set; }
            public string phoneNumber { get;set; }
            public string date { get; set; }

            public string address { get; set; }
        }
        public string padMsg(string msg, int len)
        {
            while (msg.Length < len)
            {
                msg = "0" + msg;
            }
            return msg;
        }
        private void onClick_SignUp(object sender, RoutedEventArgs e)
        {
            var signUp_info = new SignUpRequest
            {
                username = SignUpUsername.Text,
                password = SignUpPassword.Password,
                email = SignUpEmail.Text,
                phoneNumber = SignUpPhoneNumber.Text,
                date = SignUpDate.Text, 
                address = "aa, 11, bb"
            };

            string jsonString = JsonSerializer.Serialize(signUp_info);
            string len = padMsg(jsonString.Length.ToString(), 4);

            string to_send = "0" + len + jsonString;

            SendInfrmaionToServer(to_send);
        }
    }
}
