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

namespace ZuneLikeWindow.Views
{
	/// <summary>
	/// MainWindow.xaml の相互作用ロジック
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			this.InitializeComponent();

			this.MouseLeftButtonDown += (sender, e) => this.DragMove();

            CppToCS.Interface hoge = null;
            //var asm = System.Reflection.Assembly.LoadFrom("../../TerrainCreater.dll");
            var asm = System.Reflection.Assembly.LoadFrom("../../CppMain.dll");

            foreach (var t in asm.GetTypes())
            {
                if (t.IsInterface) continue;
                hoge = Activator.CreateInstance(t) as CppToCS.Interface;
                if (hoge != null)
                {
                    break;
                }
            }

            if (hoge != null)
            {
                //this.ToolArea.Children.Add(hoge);
                byte[] n = { 0, 3, 5 };
                hoge.ProcessCommand(n, 3);
            }
            else
            {

            }
        }

        private void HideButtonClick(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }

        private void MaximizeButtonClick(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Maximized;
        }

        private void MinimizeButtonClick(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Normal;
        }

        private void CloseButtonClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}