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
        private UserControl child;

        public CloseTabItem(CloseTab _parent, UserControl uc, ImageSource ImgSrc, string name = "New Tab")
        {
            InitializeComponent();

            parent = _parent;

            this.TabText.Text = name;

            child = uc;

            this.SelfImg.Source = ImgSrc;

            this.MouseLeftButtonDown += (s, e) => Active();
        }

        private void RemoveTab(object sender, RoutedEventArgs e)
        {
            parent.RemoveTab(this);
        }

        public void Active()
        {
            if(this.parent.activeTab != null)
                this.parent.activeTab.Desactive();

            this.parent.activeTab = this;

            this.Inner.Background = Brushes.White;

            this.parent.toolArea.Children.Clear();
            this.parent.toolArea.Children.Add(this.child);
        }

        private void Desactive()
        {
            this.Inner.Background = Brushes.LightSlateGray;
        }
    }
}
