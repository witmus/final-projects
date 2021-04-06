using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public abstract class MoneyFlow
    {
        public float amount { get; set; }
        public string creatorName { get; set; }
        public string date { get; set; }
        public string description { get; set; }
        public bool ifChilds { get; set; }


        protected MoneyFlow() { }

        protected MoneyFlow(float amount, string creatorName, string date, string description, bool ifChilds)
        {
            this.amount = amount;
            this.creatorName = creatorName;
            this.date = date;
            this.description = description;
            this.ifChilds = ifChilds;
        }

        public virtual void Add()
        {
        }
    }
}
