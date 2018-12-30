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
    /// CloseTabItem.xaml の相互作用ロジック
    /// </summary>
    /// 

    public partial class CloseTabItem : UserControl
    {
        private CloseTab parent;
        private StackPanel child;

        public CloseTabItem(CloseTab _parent, string name = "New Tab")
        {
            InitializeComponent();

            parent = _parent;

            tabText.Text = name;
        }

        private void RemoveTab(object sender, RoutedEventArgs e)
        {
            parent.RemoveTab(this);
        }
    }
}
