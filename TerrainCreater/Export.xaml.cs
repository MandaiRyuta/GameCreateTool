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
using System.Windows.Threading;
using Xceed.Wpf.Toolkit;

namespace TerrainCreater
{
    /// <summary>
    /// Export.xaml の相互作用ロジック
    /// </summary>
    public partial class Export : UserControl
    {
        DirectX.MainWindow window = null;

        private DispatcherTimer dispatchertimer;
        public uint Terrain_div_x;
        public uint Terrain_div_y;
        public float Terrain_Frequency;
        public float Terrain_height;
        public float Terrain_size_x;
        public float Terrain_size_y;

        float moveAddX, moveAddZ;
        float moveMinusX, moveMinusZ;
        float rot_x01,rot_x02, rot_y01,rot_y02;

        public Export()
        {
            Loaded += (s, e) => OnLoad();

            Unloaded += (s, e) => OnUnLoad();

            rot_x01 = 0.0f;
            rot_y01 = 0.0f;
            rot_x02 = 0.0f;
            rot_y02 = 0.0f;

            moveAddX = 0.0f;
            moveAddZ = 0.0f;
            moveMinusX = 0.0f;
            moveMinusZ = 0.0f;

            dispatchertimer = new DispatcherTimer();
            dispatchertimer.Tick += new EventHandler(Run);
            dispatchertimer.Interval = new TimeSpan(0, 0, 0, 0, 1000 / 60);
            dispatchertimer.Start();
        }

        private void Run(object sender, EventArgs e)
        {
            if (Keyboard.GetKeyStates(Key.W) == KeyStates.Down)
            {
                moveAddZ = 0.5f;
            }
            else
            {
                moveAddZ = 0.0f;
            }

            if (Keyboard.GetKeyStates(Key.A) == KeyStates.Down)
            {
                moveMinusX = -0.5f;
            }
            else
            {
                moveMinusX = 0.0f;
            }

            if (Keyboard.GetKeyStates(Key.D) == KeyStates.Down)
            {
                moveAddX = 0.5f;
            }
            else
            {
                moveAddX = 0.0f;
            }


            if (Keyboard.GetKeyStates(Key.S) == KeyStates.Down)
            {
                moveMinusZ = -0.5f;
            }
            else
            {
                moveMinusZ = 0.0f;
            }

            if(Keyboard.GetKeyStates(Key.Right) == KeyStates.Down)
            {
                rot_y01 = (float)Math.Cos(5.0f);
                if (window != null)
                    window.ExCameraChangeYaw(rot_y01);
            }
            else
            {
                rot_y01 = 0.0f;
            }

            if(Keyboard.GetKeyStates(Key.Left) == KeyStates.Down)
            {
                rot_y02 = -(float)Math.Cos(5.0f);
                if(window != null)
                    window.ExCameraChangeYaw(rot_y02);
            }
            else
            {
                rot_y02 = 0.0f;
            }

            if(Keyboard.GetKeyStates(Key.Up) == KeyStates.Down)
            {
                rot_x01 = -(float)Math.Cos(5.0f);
                if (window != null)
                    window.ExCameraChangePitch(rot_x01);
            }
            else
            {
                rot_x01 = 0.0f;
            }

            if(Keyboard.GetKeyStates(Key.Down) == KeyStates.Down)
            {
                rot_x02 = (float)Math.Cos(5.0f);
                if (window != null)
                    window.ExCameraChangePitch(rot_x02);
            }
            else
            {
                rot_x02 = 0.0f;
            }
            if(window != null)
            {
                float axisZ = moveMinusZ + moveAddZ;
                float axisX = moveMinusX + moveAddX;
                window.ExCameraChangeSide(axisX);
                window.ExCameraChangeUpDown(axisZ);
                window.ExCameraUpdate();
            }
        }

        private void OnUnLoad()
        {
            if(window != null)
                window.Hide();
        }

        private void OnLoad()
        {
            if(window == null)
            {
                window = new DirectX.MainWindow();
                window.Owner = Window.GetWindow(this);
                Terrain_div_x = 100;
                Terrain_div_y = 100;
                Terrain_Frequency = 0.0f;
                Terrain_height = 1.0f;
                Terrain_size_x = 100.0f;
                Terrain_size_y = 100.0f;
            }

            window.Show();

            window.ExCreateTerrain(Terrain_div_x, Terrain_div_y, Terrain_Frequency, Terrain_height, Terrain_size_x, Terrain_size_y);

            if (window != null)
                window.ExInitCamera(0.0f, 15.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

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