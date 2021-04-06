using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public class Balance
    {
        public int balanceId { get; set; }
        public ICollection<User> user { get; set; }

        public double currentBalance { get; set; }


        public Balance() { }

        public Balance(double currBalance)
        {
            currentBalance = currBalance;
        }
    }
}
