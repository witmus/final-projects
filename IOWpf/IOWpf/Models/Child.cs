using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public class Child : User
    {
        public Child() { }

        public Child(string name, string password) : base(name, password) { }

        public void NewBalanceId()
        {
            var temp = new Balance();
            using(var db = new ApplicationContext())
            {
                db.balances.Add(temp);
                temp = db.balances.OrderByDescending(p => p.balanceId).FirstOrDefault();
                db.SaveChanges();
            }
            this.balanceId = temp.balanceId+1;
        }
    }
}
