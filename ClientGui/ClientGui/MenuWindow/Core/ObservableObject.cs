using System;


using System.ComponentModel;
using System.Runtime.CompilerServices;
namespace ClientGui.MenuWindow.Core
{
    class ObservableObject : INotifypropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged([CallerMemberName] string name = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));  
        }
    }
}
