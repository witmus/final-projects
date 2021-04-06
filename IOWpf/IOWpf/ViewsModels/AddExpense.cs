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

    public class AddExpense : INotifyPropertyChanged
    {
        private Expense exp = new Expense();
        private ExpenseCategory exp_cat = new ExpenseCategory();
        private Category cat = new Category();
        private List<String> selected_categories = new List<string>();
        public ObservableCollection<String> CategoryList { get; set; }

        public AddExpense()
        {
            this.CategoryList = new ObservableCollection<string>(cat.GetList());
        }
        private String _titleString = "Wydatek:";
        public String titleString
        {
            get { return _titleString; }
            set
            {
                if(value!= _titleString)
                {
                    _titleString = value;
                    onPropertyChanged(nameof(titleString));
                }
            }
        }

        private String _catString = "";
        public String catString
        {
            get { return _catString; }
            set
            {
                if(value!=_catString)
                {
                    _catString = value;
                    onPropertyChanged(nameof(catString));
                }
            }
        }

        private String _pathString;
        public String pathString
        {
            get
            {
                return _pathString;
            }
            set
            {
                if (value != _pathString)
                {
                    _pathString = value;
                    onPropertyChanged(nameof(pathString));
                }
            }
        }

        public double amount
        {
            get { return exp.amount; }
            set
            {
                exp.amount = (float)value;
                onPropertyChanged(nameof(amount));
            }
        }

        public string date
        {
            get { return exp.date; }
            set
            {
                exp.date = value;
                onPropertyChanged(nameof(date));
            }
        }

        public string description
        {
            get { return exp.description; }
            set
            {
                exp.description = value;
                onPropertyChanged(nameof(description));
            }
        }
        

        private ICommand _path;
        public ICommand path
        {
            get
            {
                if (_path == null)
                {
                    _path = new RelayCommand(param => this.GetPath(), param => this.CanPath());
                }
                return _path;
            }
        }

        private bool CanPath()
        {
            return true;
        }

        private void GetPath()
        {

            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                exp.billPhotoPath = openFileDialog.FileName;
                pathString = exp.billPhotoPath;
            }
        }

        

        private ICommand _saveCommand;
        public ICommand SaveCommand
        {
            get
            {
                exp.creatorName = MainWindow.user.name;
                if(MainWindow.user.GetType().ToString()=="IOWpf.Models.Child")
                    exp.ifChilds = true;
                else
                    exp.ifChilds = false;
                exp.userId = MainWindow.user.ID;
                if (_saveCommand == null)
                {
                    _saveCommand = new RelayCommand(SaveObject,CanSave);
                }
                return _saveCommand;
            }
        }

        private bool CanSave(Object param)
        {
            if (exp.amount == 0 || exp.date == "" )
                return false;
            return true;
        }

        private void SaveObject(Object param)
        {      
            System.Collections.IList items = (System.Collections.IList)param;
            if (items.Count != 0)
            {
                var collection = items.Cast<String>();
                exp.Add();
                foreach (var item in collection)
                {
                    exp_cat.NewItem(item);
                }
            }
        }

        private ICommand _addCat;
        public ICommand addCat
        {
            get
            {
                if (_addCat == null)
                {
                    _addCat = new RelayCommand(param => this.addWindow(), param => this.canAddCategory());
                }
                return _addCat;
            }
        }

        private void addWindow()
        {
            if(_titleString=="Wydatek:")
            {
                titleString = "Wpisz nazwę kategorii i naciśnij dodaj:";
            }
            else
            {
                if (_titleString != "Wpisz nazwę kategorii i naciśnij dodaj"&&_catString!="")
                {
                    cat.AddCategory(_catString);
                    this.CategoryList.Add(_catString);
                    titleString = "Wydatek:";
                    catString = "";
                }
            }
        }

        private bool canAddCategory()
        {
            return true;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void onPropertyChanged(string property_name)
        {
            if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs(property_name));
        }
    }
}
