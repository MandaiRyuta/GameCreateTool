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
        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Initialize(IntPtr hwnd, int size_x, int size_y);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Run();

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

            Window window = new Window1();
            window.Show();

            HwndSource source = (HwndSource)HwndSource.FromVisual(window);

            IntPtr handle = source.Handle;

            Initialize(handle, 1280, 720);
            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Tick += new EventHandler(Run);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 1000 / 60);
            dispatcherTimer.Start();
        }

        private void Run(object sender, EventArgs e)
        {
            Run();
        }

        public void RemoveTab(CloseTabItem tab)
        {
            tabs.Remove(tab);
            closeableTabs.Children.Remove(tab);
        }
    }
}
