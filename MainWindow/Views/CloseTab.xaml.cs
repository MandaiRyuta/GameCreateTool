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
        public CloseTabItem activeTab;
        public StackPanel toolArea;

        public CloseTab(StackPanel _toolArea)
        {            
            InitializeComponent();

            tabs = new CloseTabItemCollection();

            toolArea = _toolArea;
        }

        private void AddTab(object sender, RoutedEventArgs e)
        {
            //CloseTabItem tab = new CloseTabItem(this);

            //tabs.Add(tab);
            //closeableTabs.Children.Add(tab);

            //activeTab = tab;
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
