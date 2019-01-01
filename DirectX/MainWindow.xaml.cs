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

namespace DirectX
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Initialize(IntPtr hwnd, int size_x, int size_y);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Run();

        private DispatcherTimer dispatcherTimer;

        public MainWindow()
        {
            InitializeComponent();
            
            this.MouseLeftButtonDown += (sender, e) => this.DragMove();

            Activated += (s, e) => OnActivated();
        }

        private void Run(object sender, EventArgs e)
        {
            Run();
        }

        private void OnActivated()
        {
            HwndSource source = (HwndSource)HwndSource.FromVisual(this);

            IntPtr handle = source.Handle;

            Initialize(handle, 1280, 720);
            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Tick += new EventHandler(Run);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 1000 / 60);
            dispatcherTimer.Start();
        }
    }
}
