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
using System.Net.Sockets;
using System.Net;
using ClientGui.MenuWindow;
using System.Text.Json;
using Newtonsoft.Json;
namespace ClientGui.MenuPages
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        Socket mysock;
        string name;
        public JoinRoom(Socket client, string userName)
        {
            InitializeComponent();

            mysock = client;
            name = userName;

        }
    }
}
