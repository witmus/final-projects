using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public class ExpenseCategory
    {
        public int expenseId { get; set; }
        public Expense expense { get; set; }


        public int categoryId { get; set; }
        public Category category { get; set; }

        public void NewItem(string cat)
        {
            using (var db = new ApplicationContext())
            {
                var category = db.categories.First(i => i.categoryName == cat);
                var expen = db.expenses.OrderByDescending(p => p.expenseId).FirstOrDefault();

                var Exp_Cat = new ExpenseCategory
                {
                    expense = expen,
                    category=category
                };

                db.expenseCategories.Add(Exp_Cat);
                db.SaveChanges();
            }           
        }
    }
}
