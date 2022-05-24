using ClientGui.MenuWindow.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientGui.MenuWindow.MVVM.ViewModel
{
    class MenuViewModel : ObservableObject
    {
        public HomeViewModel HomeVM { get; set; }
        private object _currentView;
        public object CurrectView
        {
            get { return _currentView; }
            set
            {
                _currentView = value;
                OnPropertyChanged();
            }
        }
        public MenuViewModel()
        {
            HomeVM = new HomeViewModel();
            CurrectView = HomeVM;
        }
    }
}
