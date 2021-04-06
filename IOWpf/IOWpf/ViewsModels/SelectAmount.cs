using IOWpf.Commands;
using IOWpf.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace IOWpf.ViewsModels
{
    class SelectAmount : INotifyPropertyChanged
    {
        private PiggyBank pBank = new PiggyBank();
        private float operationAmount;

        public float amount
        {
            set
            {
                operationAmount = (float)value;
                onPropertyChanged(nameof(amount));
            }
            get
            {
                return operationAmount;
            }
        }

        public int id
        {
            set
            {
                pBank.piggyBankId = (int)value;
                onPropertyChanged(nameof(id));
            }
        }

        private ICommand _Deposit;
        private ICommand _Withdraw;
        private ICommand _Delete;

        public ICommand Deposit
        {
            get
            {
                if(_Deposit == null)
                {
                    _Deposit = new RelayCommand(param => this.deposit(), param => this.CanTransfer());
                }
                return _Deposit;
            }
        }
        public ICommand Withdraw
        {
            get
            {
                if (_Withdraw == null)
                {
                    _Withdraw = new RelayCommand(param => this.withdraw(), param => this.CanTransfer());
                }
                return _Withdraw;
            }
        }
        public ICommand Delete
        {
            get
            {
                if (_Delete == null)
                {
                    _Delete = new RelayCommand(param => this.delete(), param => this.CanDelete());
                }
                return _Delete;
            }
        }

        private bool CanTransfer()
        {
            if(amount == 0 || pBank.piggyBankId == 0)
            {
                return false;
            }
            return true;
        }
        private bool CanDelete()
        {
            if (pBank.piggyBankId == 0)
            {
                return false;
            }
            return true;
        }

        private void deposit()
        {
            pBank.Deposit(amount);
            Window current = Application.Current.Windows.OfType<Window>().SingleOrDefault(w => w.IsActive);
            current.Close();
            MainWindow main = (MainWindow)Application.Current.MainWindow;
            main.PiggyBankClicked(null, null);
        }

        private void withdraw()
        {
            pBank.Withdraw(amount);
            Window current = Application.Current.Windows.OfType<Window>().SingleOrDefault(w => w.IsActive);
            current.Close();
            MainWindow main = (MainWindow)Application.Current.MainWindow;
            main.PiggyBankClicked(null, null);
        }
        private void delete()
        {
            pBank.Delete();
            Window current = Application.Current.Windows.OfType<Window>().SingleOrDefault(w => w.IsActive);
            current.Close();
            MainWindow main = (MainWindow)Application.Current.MainWindow;
            main.PiggyBankClicked(null, null);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void onPropertyChanged(string property_name)
        {
            if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs(property_name));
        }
    }
}
