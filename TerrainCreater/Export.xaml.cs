using System;
using System.Collections.Generic;
using System.Diagnostics;
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
using Xceed.Wpf.Toolkit;

namespace TerrainCreater
{
    /// <summary>
    /// Export.xaml の相互作用ロジック
    /// </summary>
    public partial class Export : UserControl
    {
        DirectX.MainWindow window = null;

        public uint Terrain_div_x;
        public uint Terrain_div_y;
        public float Terrain_Frequency;
        public float Terrain_height;
        public float Terrain_size_x;
        public float Terrain_size_y;

        public Export()
        {
            InitializeComponent();

            Loaded += (s, e) => OnLoad();
        }

        private void OnLoad()
        {
            Terrain_div_x = 100;
            Terrain_div_y = 100;
            Terrain_Frequency = 0.0f;
            Terrain_height = 1.0f;
            Terrain_size_x = 100.0f;
            Terrain_size_y = 100.0f;

            window = new DirectX.MainWindow();

            window.Show();

            window.ExDefaultSetView();

            window.ExCreateTerrain(Terrain_div_x, Terrain_div_y, Terrain_Frequency, Terrain_height, Terrain_size_x, Terrain_size_y);
        }

        private void WidthChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;
            Terrain_size_x = (float)d.Value;         
           
            if(window != null)
                window.ExSetTerrain(Terrain_div_x,Terrain_div_y, Terrain_Frequency, Terrain_height, Terrain_size_x, Terrain_size_y);
        }

        private void HeightChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;
            Terrain_height = (float)d.Value;

            if (window != null)
                window.ExSetTerrain(Terrain_div_x, Terrain_div_y, Terrain_Frequency, Terrain_height, Terrain_size_x, Terrain_size_y);
        }

        private void DepthChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;
            Terrain_size_y = (float)d.Value;
            if (window != null)
                window.ExSetTerrain(Terrain_div_x, Terrain_div_y, Terrain_Frequency, Terrain_height, Terrain_size_x, Terrain_size_y);
        }

        private void Div_XChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            IntegerUpDown d = (IntegerUpDown)sender;
            Terrain_div_x = (uint)d.Value;
            if (window != null)
                window.ExSetTerrain(Terrain_div_x, Terrain_div_y, Terrain_Frequency, Terrain_height, Terrain_size_x, Terrain_size_y);
        }

        private void Div_YChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            IntegerUpDown d = (IntegerUpDown)sender;
            Terrain_div_y = (uint)d.Value;
            if (window != null)
                window.ExSetTerrain(Terrain_div_x, Terrain_div_y, Terrain_Frequency, Terrain_height, Terrain_size_x, Terrain_size_y);
        }

        private void Frequency_Changed(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            double d = Math.Round(e.NewValue, 0);
            Terrain_Frequency = (float)d;
            if (window != null)
                window.ExSetTerrain(Terrain_div_x, Terrain_div_y, Terrain_Frequency, Terrain_height, Terrain_size_x, Terrain_size_y);
        }
    }
}
﻿using System;
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

namespace TerrainCreater
{
    /// <summary>
    /// Export.xaml の相互作用ロジック
    /// </summary>
    public partial class Export : UserControl
    {
        public Export()
        {
            InitializeComponent();

        }
    }
}
