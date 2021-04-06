using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public class Admin : GrownUp
    {
        public Admin() 
        {
            name = "Unlogged";
        }

        public Admin(string name, string password) : base(name, password) { }

        public override void AddToBase(String name, String password, int type)
        {
            using(var db = new ApplicationContext())
            {
                if(type==1)
                {
                    var temp = new GrownUp();
                    temp.name = name;
                    temp.password = password;
                    temp.balanceId = 1;
                    db.grownUps.Add(temp);
                }
                if(type==2)
                {
                    var temp = new Child();
                    temp.name = name;
                    temp.password = password;
                    temp.NewBalanceId();
                    db.children.Add(temp);
                }
                if(type==3)
                {
                    var temp = new Admin();
                    temp.name = name;
                    temp.password = password;
                    temp.balanceId = 1;
                    db.admins.Add(temp);
                }

                db.SaveChanges();
            }
        }

       
    }
}
