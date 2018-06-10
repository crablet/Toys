using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace LearnUWPCSharp
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            var titleBar = ApplicationView.GetForCurrentView().TitleBar;
            var deepPink = Color.FromArgb(255, 255, 20, 147);
            var hotPink = Color.FromArgb(255, 255, 105, 180);
            var darkPink = Color.FromArgb(255, 215, 0, 107);
            titleBar.BackgroundColor = deepPink;
            titleBar.ButtonBackgroundColor = deepPink;
            titleBar.ButtonHoverBackgroundColor = hotPink;
            titleBar.ButtonPressedBackgroundColor = darkPink;
            titleBar.InactiveBackgroundColor = titleBar.InactiveForegroundColor = hotPink;
            titleBar.ButtonInactiveBackgroundColor = hotPink;

            ContentFrame.Navigate(typeof(HomePage));
        }

        private void NavView_Loaded(object sender, RoutedEventArgs e)
        {
            // you can also add items in code behind
            NavView.MenuItems.Add(new NavigationViewItemSeparator());
            NavView.MenuItems.Add(new NavigationViewItem()
            { Content = "收藏", Icon = new SymbolIcon(Symbol.Folder), Tag = "content" });

            // set the initial SelectedItem 
            foreach (NavigationViewItemBase item in NavView.MenuItems)
            {
                if (item is NavigationViewItem && item.Tag.ToString() == "home")
                {
                    NavView.SelectedItem = item;
                    break;
                }
            }
        }

        private void NavView_ItemInvoked(NavigationView sender, NavigationViewItemInvokedEventArgs args)
        {
            if (args.IsSettingsInvoked)
            {
                ContentFrame.Navigate(typeof(SettingsPage));
            }
            else
            {
                // find NavigationViewItem with Content that equals InvokedItem
                var item = sender.MenuItems.OfType<NavigationViewItem>().First(x => (string)x.Content == (string)args.InvokedItem);
                NavView_Navigate(item as NavigationViewItem);
            }
        }

        private void NavView_Navigate(NavigationViewItem item)
        {
            switch (item.Tag)
            {
                case "Home":
                    ContentFrame.Navigate(typeof(HomePage));
                    break;

                case "Tasks":
                    ContentFrame.Navigate(typeof(TasksPage));
                    break;

                case "Contests":
                    ContentFrame.Navigate(typeof(ContestsPage));
                    break;

                case "Friends":
                    ContentFrame.Navigate(typeof(FriendsPage));
                    break;

                case "content":
                    ContentFrame.Navigate(typeof(MyContentPage));
                    break;
            }
        }
    }
}
