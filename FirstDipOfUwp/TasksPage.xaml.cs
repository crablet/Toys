using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace LearnUWPCSharp
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class TasksPage : Page
    {
        private TasksPageViewModel vm;
        public TasksPage()
        {
            this.InitializeComponent();

            this.vm = new TasksPageViewModel
            {
                Dates = new ObservableCollection<Date>()
            };

            this.DataContext = vm;
        }

        private DateTimeOffset NewDate { get; set; } = DateTimeOffset.Now;
        private void AddNewDate(object sender, DatePickerValueChangedEventArgs e)
        {
            NewDate = this.DatePicker.Date;
        }

        private TimeSpan NewTime { get; set; } = TimeSpan.Zero;
        private void AddNewTime(object sender, TimePickerValueChangedEventArgs e)
        {
            NewTime = this.TimePicker.Time;
        }

        private void DeleteTask(object sender, RoutedEventArgs e)
        {
            if (this.vm.SelectedTask != null)
            {
                this.vm.Dates.Remove(this.vm.SelectedTask);
            }
        }

        private void AddNewTask(object sender, RoutedEventArgs e)
        {
            this.vm.Dates.Add(new Date() { MyDate = this.NewDate.ToString() + this.NewTime.ToString() });
        }
    }

    public class Date : INotifyPropertyChanged
    {
        private string date;
        public string MyDate
        {
            get
            {
                return date;
            }
            set
            {
                date = value;
                var handler = this.PropertyChanged;
                handler?.Invoke(this, new PropertyChangedEventArgs(nameof(MyDate)));
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
    }

    public class TasksPageViewModel
    {
        public ObservableCollection<Date> Dates { get; set; }
        public Date SelectedTask { get; set; }
    }
}
