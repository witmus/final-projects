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
using System.Windows.Navigation;
using System.Windows.Shapes;
using IOWpf.Models;
using IOWpf.Views;

namespace IOWpf
{
    /// <summary>
    /// Logika interakcji dla klasy MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static List<Expense> expensesList;
        public static List<Income> incomesList;
        public static List<PiggyBank> piggyBanksList;
        public static List<Balance> ballancesLst;
        public static List<ExpenseCategory> expenseCategoriesList;
        public static List<Category> categoriesList;
        public static User user = new Admin();

    public MainWindow()
        {
            InitializeComponent();
            using (var db = new ApplicationContext())
            {
                expensesList = db.expenses.ToList();
                incomesList = db.incomes.ToList();
                piggyBanksList = db.piggyBanks.ToList();
                ballancesLst = db.balances.ToList();
                expenseCategoriesList = db.expenseCategories.ToList();
                categoriesList = db.categories.ToList();
                if(incomesList.FirstOrDefault()!=null)
                incomesList[0].checkCyclic();
            }

            DataContext = new Login();
        }

        private void ButtonFechar_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void GridBarTitle_MouseDown(object sender, MouseButtonEventArgs e)
        {
            DragMove();
        }

        private void  PanelViewClicked(object sender, RoutedEventArgs e)
        {
            if(user.name!="Unlogged")
            DataContext = new PanelView();

                // ------------- Create --------------- //
                //Balance newBalance = new Balance(1200.0);
                //db.Balances.Add(newBalance);
                //db.SaveChanges();
                /*
                Grown_up adult = new Grown_up();
                adult.name = "Tomek";
                adult.password = "qwerty12345";
                adult.BalanceId = 1;
                db.Grown_Ups.Add(adult);
                db.SaveChanges();
                */
                //Income newIncome = new Income();
                //newIncome.amount = 1000;
                //db.Incomes.Add(newIncome);
                //db.SaveChanges();

                // -------------- Read ---------------- //
                //List<Balance> lists = db.Balances.ToList();
                //ICollection<Balance> balans = lists;

                // ------------- Update ---------------- //
                //Balance firstBalance = db.Balances.FirstOrDefault();
                //firstBalance.curr_balance = 1337.00;
                //db.SaveChanges();

                // -------------- Delete ---------------- //
                //Balance firstBalance = db.Balances.FirstOrDefault();
                //db.Balances.Remove(firstBalance);
                //db.SaveChanges();

        }

        private void AddExpenseClicked(object sender, RoutedEventArgs e)
        {
            if (user.name != "Unlogged")
                DataContext = new AddExpense();
        }

        private void AddIncomeClicked(object sender, RoutedEventArgs e)
        {
            if (user.name != "Unlogged")
                DataContext = new AddIncome();
        }

        public void PiggyBankClicked(object sender, RoutedEventArgs e)
        {
            if (user.name != "Unlogged")
                DataContext = new PiggyBankView();
        }

        private void StatsClicked(object sender, RoutedEventArgs e)
        {
            if (user.name != "Unlogged")
                DataContext = new Stats();
        }

        public void AddPiggyBankClicked(object sender, RoutedEventArgs e)
        {
            if (user.name != "Unlogged")
                DataContext = new AddPiggyBankView();
        }

        public void LoginClicked(object sender, RoutedEventArgs e)
        {
            if (user.name != "Unlogged")
                DataContext = new Login();
        }

        public void AddUserClicked(object sender, RoutedEventArgs e)
        {
            if (user.name != "Unlogged")
                DataContext = new AddUser();
        }
    }
       
}
