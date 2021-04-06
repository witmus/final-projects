using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mime;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;


namespace IOWpf.Models
{
    public class Income : MoneyFlow
    {
        public int incomeId { get; set; }
        public int? userId { get; set; }                            // Foreign key 
        public virtual User user { get; set; }                       // Income is associated with one User

        public Income() { }

        public Income(float amount, string creatorName, string date, string description, bool ifChilds) : base(amount, creatorName, date, description, ifChilds) { }

        public override void Add()
        {
            using (var db = new ApplicationContext())
            {
                Income inc = new Income();
                inc.amount = amount;
                inc.date = date;
                inc.creatorName = creatorName;
                inc.description = description;
                inc.userId = userId;
                inc.ifChilds = ifChilds;
                
                db.incomes.Add(inc);

                var balance = db.balances.SingleOrDefault(b => b.balanceId == MainWindow.user.balanceId); 
                if (balance != null)
                {
                    balance.currentBalance += inc.amount;
                }

                db.SaveChanges();
                MainWindow.incomesList = db.incomes.ToList();
                MainWindow.ballancesLst = db.balances.ToList();
            }
        }

        public double Summing(string startDate, string endDate)
        {

            var sum = 0.0;

            for (int i = 0; i < MainWindow.incomesList.Count; i++)
            {
                if (startDate != null && endDate != null)
                {
                    if (DateTime.Parse(MainWindow.incomesList[i].date) >= DateTime.Parse(startDate) &&
                        DateTime.Parse(MainWindow.incomesList[i].date) <= DateTime.Parse(endDate))
                    {
                        sum += MainWindow.incomesList[i].amount;

                    }
                }

                else if (MainWindow.incomesList[i].userId == MainWindow.user.ID)
                {
                    sum += MainWindow.incomesList[i].amount;
                }

            }

            return sum;
        }

        public void checkCyclic()
        {
            List<Income> incomes;
            using (var db = new ApplicationContext())
            {
                incomes = db.incomes.ToList();
                foreach (var income in incomes)
                {
                    if (income.description != null)
                    { 
                        if (income.description.Substring(income.description.Length - 3) == "(c)")
                        {
                            if (DateTime.Now.AddMonths(-1).ToString("dd.MM.yyyy") == income.date)
                            {
                                 bool check = true;
                                foreach(var income2 in incomes)
                                {
                                    if ((income2.date == DateTime.Now.ToString("dd.MM.yyyy")) && (income2.description == income.description))
                                        check = false;
                                }
                                if (check)
                                {
                                    income.date = Convert.ToDateTime(income.date).AddMonths(1).ToString("dd.MM.yyyy");
                                    income.Add();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
