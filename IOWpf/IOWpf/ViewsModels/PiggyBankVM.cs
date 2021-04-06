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
    using System.Windows.Input;
    using System.Windows.Controls;
    using System.Diagnostics;
    using System.Collections.ObjectModel;
    using System.Windows;

    public class PiggyBankVM : INotifyPropertyChanged
    {
        List<PiggyBank> banksList = new List<PiggyBank>();

        public ObservableCollection<PiggyBank> list { get; set; }
        public PiggyBankVM()
        {          
            if (MainWindow.user.GetType().ToString() == "IOWpf.Models.Admin")
            {
                banksList = MainWindow.piggyBanksList;
            }
            else
            {
                foreach (PiggyBank pb in MainWindow.piggyBanksList)
                {
                    if (pb.creatorName == MainWindow.user.name)
                    {
                        banksList.Add(pb);
                    }
                }
            }
            this.list = new ObservableCollection<PiggyBank>(banksList);
        }

        private ICommand _addBankClicked;
        public ICommand addBankClicked
        {
            get
            {
                if (_addBankClicked == null)
                {
                    _addBankClicked = new RelayCommand(param => this.addBank());
                }
                return _addBankClicked;
            }
        }

        private void addBank()
        {
            MainWindow mw = (MainWindow)Application.Current.MainWindow;
            mw.AddPiggyBankClicked(null, null);
        }

        private ICommand _operationClicked;
        public ICommand operationClicked
        {
            get
            {
                if (_operationClicked == null)
                {
                    _operationClicked = new RelayCommand(param => this.operation());
                }
                return _operationClicked;
            }
        }

        private void operation()
        {
            Views.SelectAmount wk = new Views.SelectAmount();
            wk.Show();
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void onPropertyChanged(string property_name)
        {
            if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs(property_name));
        }
    }
}
