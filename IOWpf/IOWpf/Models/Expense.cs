using LiveCharts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mime;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace IOWpf.Models
{
    public class Expense : MoneyFlow
    {
        public int expenseId { get; set; }
        public string billPhotoPath { get; set; }

        public int? userId { get; set; }                             // Foreign key 
        public virtual User user { get; set; }                       // Expense is associated with one User
        public virtual ICollection<ExpenseCategory> expenseCategories { get; set; }
        

        public Expense() { }

     
        public Expense(float amount, string creatorName, string date, string description, bool ifChilds, string bill_photo_path) : base(amount, creatorName, date, description, ifChilds)
        {
            this.billPhotoPath = bill_photo_path;
        }

        public override void Add()
        {
            Expense exp = new Expense();
            exp.amount = amount;
            exp.date=date;
            exp.creatorName=creatorName;
            exp.description=description;
            exp.userId = userId;
            exp.ifChilds=ifChilds;
            exp.billPhotoPath = billPhotoPath;
            using (var db = new ApplicationContext())
            {
                db.expenses.Add(exp);

                var balance = db.balances.SingleOrDefault(b => b.balanceId == MainWindow.user.balanceId);       
                if (balance != null)
                {
                    balance.currentBalance -= exp.amount;
                }
                
                db.SaveChanges();
                MainWindow.expensesList = db.expenses.ToList();
                MainWindow.ballancesLst = db.balances.ToList();
                MainWindow.expenseCategoriesList = db.expenseCategories.ToList();
            }
        }

        public double Summing(string startDate, string endDate)
        {

            var sum = 0.0;

            for (int i = 0; i < MainWindow.expensesList.Count; i++)
            {
                if(startDate != null && endDate != null)
                {
                    if (DateTime.Parse(MainWindow.expensesList[i].date) >= DateTime.Parse(startDate) &&
                    DateTime.Parse(MainWindow.expensesList[i].date) <= DateTime.Parse(endDate))
                    {
                        sum += MainWindow.expensesList[i].amount;
                    }
                }
                
                else if (MainWindow.expensesList[i].userId == MainWindow.user.ID)
                {
                    sum += MainWindow.expensesList[i].amount;
                }
            }

            return sum;
        }

        public List<double> CategorySum(string startDate, string endDate)
        {
            List<double> returning = new List<double>();

            using (var db = new ApplicationContext())
            {
               
                MainWindow.expenseCategoriesList = db.expenseCategories.ToList();

                for (int i = 1; i <= MainWindow.categoriesList.Count; i++)
                {
                    var sum = 0.0;

                    for (int j = 0; j < MainWindow.expenseCategoriesList.Count; j++)
                    {
                        if (MainWindow.expenseCategoriesList[j].categoryId == i)
                        {
                            int k = 0;
                            while (MainWindow.expensesList[k].expenseId != MainWindow.expenseCategoriesList[j].expenseId)
                            {
                                k++;
                            }
                            if (MainWindow.expensesList[k].expenseId == MainWindow.expenseCategoriesList[j].expenseId &&
                                MainWindow.expensesList[k].userId == MainWindow.user.ID)
                            {
                                if(DateTime.Parse(MainWindow.expensesList[k].date)>DateTime.Parse(startDate)&& DateTime.Parse(MainWindow.expensesList[k].date) < DateTime.Parse(endDate))
                                sum += MainWindow.expensesList[k].amount;
                            }
                        }
                    }

                    returning.Add(sum);
                }
            }

            

            return returning;
        }

    }   
}

