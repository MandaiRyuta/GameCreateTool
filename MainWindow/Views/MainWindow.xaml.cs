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
    /// 
    public class ToolInfo
    {
        public ToolInfo(Type _type, ImageSource _imgSrc)
        {
            type = _type;
            imgSrc = _imgSrc;
        }

        public Type type;
        public ImageSource imgSrc;
    }
    
	public partial class MainWindow : Window
	{
        DispatcherTimer dispatcherTimer;
        List<ToolInfo> toolList;
        CloseTab toolTabs;

        public MainWindow()
		{
			this.InitializeComponent();

			this.MouseLeftButtonDown += (sender, e) => this.DragMove();
            
            this.Loaded += (s, e) => this.OnActivated();
        }

        private void OnActivated()
        {
            toolTabs = new CloseTab(ToolArea);

            this.toolTabArea.Children.Add(toolTabs);

            toolList = new List<ToolInfo>();

            string[] files = System.IO.Directory.GetFiles(@"../../Plugins/", "*.dll", System.IO.SearchOption.AllDirectories);
            
            foreach (var file in files)
            {
                var asm = System.Reflection.Assembly.LoadFrom(file);

                foreach (var t in asm.GetTypes())
                {
                    if (t.IsInterface) continue;
                    if (!t.IsSubclassOf(typeof(UserControl))) continue;
                    UserControl hoge = Activator.CreateInstance(t) as UserControl;
                    if (hoge != null)
                    {
                        var path = file;
                        var icon = System.Drawing.Icon.ExtractAssociatedIcon(path);
                        var source = Imaging.CreateBitmapSourceFromHIcon(icon.Handle, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());

                        Image img = new Image();
                        img.Source = source;
                        img.Stretch = Stretch.Fill;
                        ToolIcon ti = new ToolIcon(img);
                        ti.ImagePanel.Click += (s, e) => RunTool(0);
                        IconList.Children.Add(ti);

                        toolList.Add(new ToolInfo(t, source));

                        break;
                    }
                }

            }
        }

        private void RunTool(int index)
        {
            toolTabs.AddTab(Activator.CreateInstance(toolList[index].type) as UserControl, toolList[index].imgSrc);
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