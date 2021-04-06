using System.ComponentModel;

namespace IOWpf.ViewsModels
{
    using Models;
    using LiveCharts;
    using System;

    public class Stats : INotifyPropertyChanged
    {
        private Expense exp = new Expense();
        private Income inc = new Income();
        private Category category = new Category();

        private string _startDate = DateTime.Today.AddMonths(-1).ToString();
        public string startDate
        {
            get { return _startDate; }
            set
            {
                if (value != _startDate)
                {
                    _startDate = value;
                    categoriesValues = new ChartValues<double>(exp.CategorySum(_startDate, _endDate));
                    expences = exp.Summing(_startDate, _endDate) + " zł";
                    incomes = inc.Summing(_startDate, _endDate) + " zł";
                    onPropertyChanged(nameof(startDate));
                }
            }
        }

        private string _endDate = DateTime.Today.ToString();
        public string endDate
        {
            get { return _endDate; }
            set
            {
                if (value != _endDate)
                {
                    _endDate = value;
                    categoriesValues = new ChartValues<double>(exp.CategorySum(_startDate, _endDate));
                    expences=exp.Summing(_startDate, _endDate) + " zł";
                    incomes = inc.Summing(_startDate, _endDate) + " zł";
                    onPropertyChanged(nameof(endDate));
                }
            }
        }

        private string _incomes="0";
        public string incomes
        {
            set
            {
                if (value != _incomes)
                {
                    _incomes = value;
                    onPropertyChanged(nameof(incomes));
                }
            }
            get
            {
                return _incomes;
            }

        }

        private string _expences="0";
        public string expences
        {
            set
            {
                if(value!=_expences)
                {
                    _expences = value;
                    onPropertyChanged(nameof(expences));
                }
            }
            get
            {
                return _expences;
            }

        }

        private ChartValues<double> _categoriesValues;
        public ChartValues<double> categoriesValues 
        {
            set 
            { 
                if(value!=_categoriesValues)
                {
                    _categoriesValues = value;
                    onPropertyChanged(nameof(categoriesValues));
                }
            }
            get
            {
                return _categoriesValues;
            }
        }

        public ChartValues<string> categoriesNames 
        {
            get
            {
                return new ChartValues<string>(category.GetList());
            }
        }


        public event PropertyChangedEventHandler PropertyChanged;
        private void onPropertyChanged(string property_name)
        {
            if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs(property_name));
        }
    }
}
