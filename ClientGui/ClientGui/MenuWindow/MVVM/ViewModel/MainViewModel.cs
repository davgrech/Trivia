using ClientGui.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientGui.MenuWindow.MVVM.ViewModel
{
    class MainViewModel : ObservableObject
    {
        public RelayCommand HomeViewCommand { get; set; } // move to home page
        public RelayCommand UserStatisticsViewCommand { get; set; } //move to user statistics page
        public RelayCommand HighScoresViewCommand { get; set; } //move to highscores page

        public RelayCommand CreateRoomViewCommand { get; set; }


        public HomeViewModel HomeVm { get; set; } // homepage model

        public UserStatisticsViewModel userStatsVM { get; set; } // userstats model
        public HighScoresViewModel HighScoresVM { get; set; } // high scores view model
        public CreateRoomViewModel CreateRoomVM { get; set; }
        private object _currentView;

        public object CurrentView
        {
            get { return _currentView; }
            set 
            { 
                _currentView = value;
                OnPropertyChanged();
            }
        }


        public MainViewModel()
        {
            HomeVm = new HomeViewModel();
            userStatsVM = new UserStatisticsViewModel();
            HighScoresVM = new HighScoresViewModel();
            CreateRoomVM= new CreateRoomViewModel();
            CurrentView = HomeVm;

            HomeViewCommand = new RelayCommand(o => 
            {
                CurrentView = HomeVm;
            });

            UserStatisticsViewCommand = new RelayCommand(o =>
            {
                CurrentView = userStatsVM;
            });

            HighScoresViewCommand = new RelayCommand(o =>
            {
                CurrentView = HighScoresVM;
            });
            CreateRoomViewCommand = new RelayCommand(o =>
            {
                CurrentView = CreateRoomVM;
            }
            );
        }
    }
}
