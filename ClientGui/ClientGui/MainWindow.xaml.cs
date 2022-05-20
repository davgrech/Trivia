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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;
namespace ClientGui
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static Socket _clientSocket = null;

        public MainWindow()
        {
            

            InitializeComponent();
            this.Visibility = Visibility.Hidden;


            //create a sock
            _clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            
           

            //bind to the server
            ConnectToServer();

            //login handler
            loginWindow hi = new loginWindow(_clientSocket);
           
            //show login handler
            hi.Show();
        }



        //connection to the server
        private void ConnectToServer()
        {
            if (!_clientSocket.Connected)
            {
                try
                {
                    _clientSocket.Connect(IPAddress.Loopback, 2022);

                }
                catch (SocketException)
                {
                    Environment.Exit(0);
                }
            }
        }
    }
}
