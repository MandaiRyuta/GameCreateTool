using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace ZuneLikeWindow
{
    /// <summary>
    /// CloseTab.xaml の相互作用ロジック
    /// </summary>
    /// 
    using CloseTabItemCollection = List<CloseTabItem>;

    public partial class CloseTab : UserControl
    {
        private CloseTabItemCollection tabs;
        public StackPanel child = null;
        private DispatcherTimer dispatcherTimer;

        public CloseTab()
        {            
            InitializeComponent();

            tabs = new CloseTabItemCollection();
        }

        private void AddTab(object sender, RoutedEventArgs e)
        {
            CloseTabItem tab = new CloseTabItem(this);

            tabs.Add(tab);
            closeableTabs.Children.Add(tab);
            //CloseTabItem tab = new CloseTabItem(this);

            Window window = new Window1();
            window.Show();
            //tabs.Add(tab);
            //closeableTabs.Children.Add(tab);

            HwndSource source = (HwndSource)HwndSource.FromVisual(window);

            IntPtr handle = source.Handle;

            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 1000 / 60);
            dispatcherTimer.Start();
        }

        }

        public void AddTab(UserControl uc, ImageSource imgSrc)
        {
            CloseTabItem tab = new CloseTabItem(this, uc, imgSrc);
        
            tabs.Add(tab);
            closeableTabs.Children.Add(tab);
            tab.Active();
        }

        public void RemoveTab(CloseTabItem tab)
        {
            tabs.Remove(tab);
            closeableTabs.Children.Remove(tab);
        }
    }
}
