using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public class GrownUp : User
    {
        public GrownUp() { }

        public GrownUp(string name, string password) : base(name, password) { }

        public override void AddToBase(String name, String password, int type){}
    }
}
