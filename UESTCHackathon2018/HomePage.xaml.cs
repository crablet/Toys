using System;
using System.Collections.Generic;
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
    public sealed partial class HomePage : Page
    {
        public HomePage()
        {
            this.InitializeComponent();
        }

        public string password { get; set; } = string.Empty;
        private void passwordBox_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if (passwordBox.Password == "Password")
            {
                statusText.Text = "不能将密码设为\"Password\"。";
            }
            else
            {
                password = passwordBox.Password;
                statusText.Text = string.Empty;
            }
        }

        public string ID { get; set; } = string.Empty;
        private void ReadUserID(object sender, TextChangedEventArgs e)
        {
            ID = inputBox.Text;
            if (ID == "123456789")
            {
                InputStatus.Text = "输入错误";
            }
            else
            {
                InputStatus.Text = string.Empty;
            }
        }

        private void SubmitIDAndPassword(object sender, RoutedEventArgs e)
        {
            // Remained to be filled.
        }

        private void ClearIDAndPassword(object sender, RoutedEventArgs e)
        {
            this.inputBox.Text = string.Empty;
            this.ID = string.Empty;

            this.password = string.Empty;
            this.passwordBox.Password = string.Empty;
            this.passwordBox.PlaceholderText = "请输入密码";
        }
    }
}
