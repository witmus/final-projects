using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public abstract class User
    {
        public int ID { get; set; }
        public string name { get; set; }
        public string password { get; set; }

        public virtual ICollection<Income> incomes { get; set; }                        // one User to many Incomes
        public virtual ICollection<Expense> expenses { get; set; }                      // one User to many Expenses
        public virtual ICollection<UserPiggybank> userPiggyBanks { get; set; }
        public int balanceId { get; set; }                                              // foreign key
        public Balance balance { get; set; }


        protected User() 
        {
            this.incomes = new HashSet<Income>();                       // ?
            this.expenses = new HashSet<Expense>();                     // ?
        }

        protected User(string name, string password)
        {
            this.name = name;
            this.password = password;
        }

        
        public bool LoginPasswordCorrect(String password, String login)
        {
            User user = null;
            using (var db = new ApplicationContext())
            {
                user = db.children.FirstOrDefault(i => (i.name == login && i.password == password));
                if (user == null)
                {
                    user = db.admins.FirstOrDefault(i => (i.name == login && i.password == password));
                }
                if (user == null)
                {
                    user = db.grownUps.FirstOrDefault(i => (i.name == login && i.password == password));
                }
                if(user == null)
                {
                    return false;
                }
                else
                {
                    MainWindow.user = user;
                    return true;
                }
            }
        }

        public virtual void AddToBase(String name, String password, int type) { }

        public bool AdminExists()
        {
            Admin temp = new Admin();
            using (var db = new ApplicationContext())
            {
                temp = db.admins.FirstOrDefault();
            }
            if (temp == null)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}
