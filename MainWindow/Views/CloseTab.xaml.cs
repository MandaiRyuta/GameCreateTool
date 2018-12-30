using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

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
        }

        public void RemoveTab(CloseTabItem tab)
        {
            tabs.Remove(tab);
            closeableTabs.Children.Remove(tab);
        }
    }
}
