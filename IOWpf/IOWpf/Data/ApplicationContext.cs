using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Query;

namespace IOWpf.Models
{
    class ApplicationContext : DbContext
    {
        public DbSet<Balance> balances { get; set; }
        public DbSet<PiggyBank> piggyBanks { get; set; }
        public DbSet<Child> children { get; set; }
        public DbSet<GrownUp> grownUps { get; set; }
        public DbSet<Admin> admins { get; set; }
        public DbSet<Income> incomes { get; set; }
        public DbSet<Expense> expenses { get; set; }
        public DbSet<Category> categories { get; set; }
        public DbSet<UserPiggybank> userPiggyBanks { get; set; }
        public DbSet<ExpenseCategory> expenseCategories { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder options)
            => options.UseSqlite("Data Source=database.db");

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<User>().ToTable("Users");
            modelBuilder.Entity<UserPiggybank>()
                .HasKey(c => new { c.userId, c.piggyBankId });
            modelBuilder.Entity<ExpenseCategory>()
                .HasKey(c => new { c.expenseId, c.categoryId });
        }
    }
}
