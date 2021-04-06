using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public class PiggyBank
    {
        public int piggyBankId { get; set; }
        public virtual ICollection<UserPiggybank> userPiggyBanks { get; set; }

        public string creatorName { get; set; }
        public float goal { get; set; }
        public string goalDate { get; set; }
        public string goalName { get; set; }
        public bool ifChilds { get; set; }
        public float monthlyIncome { get; set; }
        public string startDay { get; set; }
        public float treasuredAmount { get; set; }


        public PiggyBank() { }

        public PiggyBank(string creatorName, float goal, string goalDate, string goalName, bool ifChilds, float monthlyIncome, string startDay, float treasuredAmount)
        {
            this.creatorName = creatorName;
            this.goal = goal;
            this.goalDate = goalDate;
            this.goalName = goalName;
            this.ifChilds = ifChilds;
            this.monthlyIncome = monthlyIncome;
            this.startDay = startDay;
            this.treasuredAmount = treasuredAmount;
        }

        public void Add()
        {
            using (var db = new ApplicationContext())
            {
                var query = from pb in db.piggyBanks
                            orderby pb.piggyBankId descending
                            select pb;
                int next_id = 1;
                if (query.Any())
                {
                    next_id = query.FirstOrDefault().piggyBankId + 1;
                }
                PiggyBank pBank = new PiggyBank();
                pBank.piggyBankId = next_id;
                pBank.treasuredAmount = treasuredAmount;
                pBank.goal = goal;
                pBank.goalName = goalName;
                if (MainWindow.user.GetType().ToString() == "IOWpf.Models.Child")
                {
                    pBank.ifChilds = true;
                }
                else
                {
                    pBank.ifChilds = false;
                }
                pBank.monthlyIncome = monthlyIncome;
                pBank.startDay = DateTime.Now.ToString("dd.MM.yyyy");
                pBank.creatorName = MainWindow.user.name;
                pBank.goalDate = goalDate;

                db.piggyBanks.Add(pBank);
                db.SaveChanges();
                MainWindow.piggyBanksList = db.piggyBanks.ToList();

            }
        }

        public void Deposit(float _amount)
        {
            int PbId = this.piggyBankId;
            using (var db = new ApplicationContext())
            {
                var query = from pb in db.piggyBanks
                            where pb.piggyBankId == PbId
                            select pb;
                if (query.Any())
                {
                    query.FirstOrDefault().treasuredAmount += _amount;
                }
                db.SaveChanges();
                MainWindow.piggyBanksList.Clear();
                MainWindow.piggyBanksList = db.piggyBanks.ToList();

            }
        }

        public void Delete()
        {
            int PbId = this.piggyBankId;
            using (var db = new ApplicationContext())
            {
                var query = from pb in db.piggyBanks
                            where pb.piggyBankId == PbId
                            select pb;
                if (query.Any())
                {
                    db.piggyBanks.Remove(query.FirstOrDefault());
                }
                query = from pb in db.piggyBanks
                        select pb;
                
                db.SaveChanges();
                MainWindow.piggyBanksList.Clear();
                MainWindow.piggyBanksList = db.piggyBanks.ToList();

            }
        }

        public void Withdraw(float _amount)
        {
            int PbId = this.piggyBankId;
            using (var db = new ApplicationContext())
            {
                var query = from pb in db.piggyBanks
                            where pb.piggyBankId == PbId
                            select pb;
                if (query.Any())
                {
                    if (query.FirstOrDefault().treasuredAmount >= _amount)
                    {
                        query.FirstOrDefault().treasuredAmount -= _amount;
                    }
                }
                db.SaveChanges();
                MainWindow.piggyBanksList.Clear();
                MainWindow.piggyBanksList = db.piggyBanks.ToList();
            }
        }
    }
}
