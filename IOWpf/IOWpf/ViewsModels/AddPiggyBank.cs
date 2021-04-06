using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace IOWpf.ViewsModels
{
    using Views;
    using Models;
    using Commands;
    using System.Windows;

    public class AddPiggyBank : INotifyPropertyChanged
    {

        private PiggyBank pBank = new PiggyBank();

        public string name
        {
            set
            {
                pBank.goalName = value;
                onPropertyChanged(nameof(name));
            }
        }

        public string date
        {
            set
            {
                pBank.goalDate = value;
                onPropertyChanged(nameof(date));
            }
        }

        public double startAmount
        {
            set
            {
                pBank.treasuredAmount = (float)value;
                onPropertyChanged(nameof(startAmount));
            }
        }

        public double targetAmount
        {
            set
            {
                pBank.goal = (float)value;
                onPropertyChanged(nameof(targetAmount));
            }
        }

        public double deposit
        {
            set
            {
                pBank.monthlyIncome = (float)value;
                onPropertyChanged(nameof(deposit));
            }
        }

        private ICommand _AddPiggyBank;

        public ICommand AddPiggyBankProp
        {
            get
            {
                pBank.creatorName = MainWindow.user.name;
                if (MainWindow.user.GetType().ToString() == "IOWpf.Models.Child")
                {
                    pBank.ifChilds = true;
                }
                else
                {
                    pBank.ifChilds = false;
                }
                if(_AddPiggyBank == null)
                {
                    _AddPiggyBank = new RelayCommand(param => this.SaveBank(), param => this.CanSave());
                }
                return _AddPiggyBank;
            }
        }

        private bool CanSave()
        {
            if (pBank.treasuredAmount < 0.0 || pBank.goalDate == "")
            {
                return false;
            }
            return true;
        }

        private void SaveBank()
        {
            pBank.Add();
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
