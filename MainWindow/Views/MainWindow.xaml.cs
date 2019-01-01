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
        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static int add(int a, int b);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Initialize(IntPtr hwnd, int size_x, int size_y);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Run();
        
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
                //byte[] n = { 0, 3, 5 };
                //hoge.ProcessCommand(n, 3);
                //hoge.
            }
            else
            {

            }
            
            
        
        }

        private void Run(object sender, EventArgs e)
        {
            Run();
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

            Initialize(handle, 1280, 720);
            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Tick += new EventHandler(Run);
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