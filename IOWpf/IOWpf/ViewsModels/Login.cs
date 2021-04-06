using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace IOWpf.ViewsModels
{
    using Views;
    using Models;
    using Commands;
    using System.Collections.ObjectModel;
    using System.Windows.Input;

    public class Login : INotifyPropertyChanged
    {


        private string _username;
        public string username
        {
            get { return _username; }
            set
            {
                _username = value;
                onPropertyChanged(nameof(username));
            }
        }


        private string _password="";
        public string password
        {
            get { return _password; }
            set
            {
                _password = value;
                onPropertyChanged(nameof(password));
            }
        }

        private string _errorLog;
        public string errorLog
        {
            get { return _errorLog; }
            set
            {
                _errorLog = value;
                onPropertyChanged(nameof(errorLog));
            }
        }


        private ICommand _loginCommand;

        public ICommand LoginCommand
        {
            get
            {

                if (_loginCommand == null)
                {
                    _loginCommand = new RelayCommand(param => this.tryLogin(), param => this.CanLog()
                    );
                }
                return _loginCommand;
            }
        }

        private bool CanLog()
        {
            if (_username == "" || _password == "")
            {
                errorLog = "Wypełnij wszystkie pola";
                return false;
            }
            if (_username == "Unlogged")
            {
                errorLog = "Unlogged jest zastrzeżoną nazwą";
                return false;
            }
            return true;
        }

        private void tryLogin()
        {
            if (MainWindow.user.LoginPasswordCorrect(_username, _password))
            {
                errorLog = "Udało się zalogować";
            }
            else
            {
                errorLog = "Nie udało się zalogować";
            }
        }


        private ICommand _AddAdminCommand;
        public ICommand AddAdminCommand
        {
            get
            {

                if (_AddAdminCommand == null)
                {
                    _AddAdminCommand = new RelayCommand(param => this.tryAdd(), param => this.CanAdd()
                    );
                }
                return _AddAdminCommand;
            }
        }

        private bool CanAdd()
        {
            if (MainWindow.user.AdminExists())
            {
                if (_username != "Unlogged" && _errorLog != "Udało się zalogować" && _errorLog != "Nie udało się zalogować")
                    errorLog = "Konto administratora już istnieje";
                return false;
            }
            if (_username == "" || _password == "" || _username ==null )
            {
                return false;
            }
            if(_username=="Unlogged")
            {
                errorLog = "Unlogged jest zastrzeżoną nazwą";
                return false;
            }
            return true;
        }

        private void tryAdd()
        {
            MainWindow.user.AddToBase(username, password, 3);
        }




        public event PropertyChangedEventHandler PropertyChanged;
        private void onPropertyChanged(string property_name)
        {
            if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs(property_name));
        }
    }
}
