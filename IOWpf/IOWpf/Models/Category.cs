using Microsoft.EntityFrameworkCore.Migrations.Operations;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IOWpf.Models
{
    public class Category
    {
        public int categoryId { get; set; }

        public string categoryName { get; set; }
        public virtual ICollection<ExpenseCategory> expenseCategories { get; set; }    
        
        /*
         * zwraca listę stringów z wszystkimi kategoriami wczytanymi z bazy danych - zamiast ,,globalnej" list z main window wczytywać liste ta metoda
         */
        public List<string> GetList()
        {
            List<String> catlist = new List<string>();

            using (var db = new ApplicationContext())
            {
                List<Category> cats = new List<Category> { };
                cats = db.categories.ToList();
                for (int i = 0; i < cats.Count(); i++)
                {
                    catlist.Add(cats[i].categoryName);
                }
            }

            return catlist;
        }


        public void AddCategory(String catname)
        {
            using (var db = new ApplicationContext())
            {
                Category category = new Category();
                category.categoryName = catname;
                db.categories.Add(category);
                db.SaveChanges();
            }
        }
    }
}
