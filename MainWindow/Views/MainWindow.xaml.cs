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

namespace ZuneLikeWindow.Views
{
	/// <summary>
	/// MainWindow.xaml の相互作用ロジック
	/// </summary>
	public partial class MainWindow : Window
	{
        DispatcherTimer dispatcherTimer;

        public MainWindow()
		{
			this.InitializeComponent();

			this.MouseLeftButtonDown += (sender, e) => this.DragMove();

           UIElement hoge = null;
            //var asm = System.Reflection.Assembly.LoadFrom("../../TerrainCreater.dll");
            var asm = System.Reflection.Assembly.LoadFrom("../../TerrainCreater.dll");

            foreach (var t in asm.GetTypes())
            {
                if (t.IsInterface) continue;
                hoge = Activator.CreateInstance(t) as UIElement;
                if (hoge != null)
                {
                    break;
                }
            }

            if (hoge != null)
            {
                this.ToolArea.Children.Add(hoge);
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

            HwndSource source = (HwndSource)HwndSource.FromVisual(this);

            IntPtr handle = source.Handle;

            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 1000 / 60);
            dispatcherTimer.Start();
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