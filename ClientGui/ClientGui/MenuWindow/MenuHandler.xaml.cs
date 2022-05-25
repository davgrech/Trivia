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
namespace ClientGui.MenuWindow
{
    /// <summary>
    /// Interaction logic for MenuHandler.xaml
    /// </summary>
    /// 
   
    public partial class MenuHandler : Window
    {

        private static Socket mySock = null;

        public MenuHandler(Socket _clientSocket)
        {
            InitializeComponent();
            mySock = _clientSocket; 


            
        }

        
    }
}
