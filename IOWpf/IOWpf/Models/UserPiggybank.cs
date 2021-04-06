using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public class UserPiggybank
    {
        public int userId { get; set; }
        public User user { get; set; }


        public int piggyBankId { get; set; }
        public PiggyBank piggyBank { get; set; }
    }
}
