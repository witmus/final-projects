using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.IO;
using System.Windows;
using Microsoft.Win32;

namespace IOWpf.ViewsModels
{

    using Views;
    using Models;
    using Commands;
    using System.Collections.ObjectModel;
    

    public class AddUser : INotifyPropertyChanged
    {
        private String _username = "";
        public String username
        {
            get { return _username; }
            set
            {
                if (value != _username)
                {
                    _username = value;
                    onPropertyChanged(nameof(username));
                }
            }
        }

        private String _password = "";
        public String password
        {
            get { return _password; }
            set
            {
                if (value != _password)
                {
                    _password = value;
                    onPropertyChanged(nameof(password));
                }
            }
        }

        private String _selectedItem;

        public String selectedItem
        {
            get { return _selectedItem;  }
            set
            {
                if (value != _selectedItem)
                {
                    _selectedItem = value;
                    onPropertyChanged(nameof(selectedItem));
                }
            }
        }


        private ICommand _addUserCommand;
        public ICommand addUserCommand
        {
            get
            {
                if (_addUserCommand == null)
                {
                    _addUserCommand = new RelayCommand(param => this.AddUserMethod(), param => this.CanAdd());
                }
                return _addUserCommand;
            }
        }

        private void AddUserMethod()
        {
            if(_selectedItem== "System.Windows.Controls.ListBoxItem: Dorosły")
            {
                MainWindow.user.AddToBase(_username,_password,1);
            }
            else if(_selectedItem=="System.Windows.Controls.ListBoxItem: Dziecko")
            {
                MainWindow.user.AddToBase(_username, _password, 2);
            }
            else if(_selectedItem == "System.Windows.Controls.ListBoxItem: Administrator")
            {
                MainWindow.user.AddToBase(_username, _password, 3);
            }
        }

        private bool CanAdd()
        {
            if (MainWindow.user.GetType().ToString() != "IOWpf.Models.Admin")
            {
                added = "Musisz być zalogowany jako administrator";
                return false;
            }
            if(_username==""||password==""||_selectedItem=="")
            {
                return false;
            }
            if(_username=="Unlogged")
            {
                added = "Unlogged to zastrzeżona nazwa";
                return false;
            }
            return true;
        }

        private String _added = "";
        public String added
        {
            get { return _added; }
            set
            {
                if (value != _added)
                {
                    _added = value;
                    onPropertyChanged(nameof(added));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void onPropertyChanged(string property_name)
        {
            if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs(property_name));
        }


    }
}
