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

namespace ClientGui.MenuPages
{
    /// <summary>
    /// Interaction logic for AdminWaitingRoom.xaml
    /// </summary>
    public partial class AdminWaitingRoom : Window
    {
        public AdminWaitingRoom(int Id, string name)
        {
            InitializeComponent();
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

        private void return_toggle(object sender, RoutedEventArgs e)
        {
            //return to menu // close room
        }

        private void start_game(object sender, RoutedEventArgs e)
        {
            //start game handle
        }


    }
    

}
