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
using System.Windows.Threading;
using Xceed.Wpf.Toolkit;

namespace SkyDomeCreator
{
    /// <summary>
    /// Export.xaml の相互作用ロジック
    /// </summary>

    public partial class Export : UserControl
    {
        DirectX.MainWindow window = null;

        private DispatcherTimer dispatchertimer;
        float cube_size_x;
        float cube_size_y;
        float cube_size_z;
        float cylinder_height;
        float cylinder_diameter;
        uint cylinder_tessellatiion;
        float sphere_diameter;
        uint sphere_tessellation;

        float moveAddX, moveAddZ;
        float moveMinusX, moveMinusZ;
        float rot_x01, rot_x02, rot_y01, rot_y02;

        public Export()
        {
            InitializeComponent();

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

            if (Keyboard.GetKeyStates(Key.Right) == KeyStates.Down)
            {
                rot_y01 = (float)Math.Cos(5.0f);
                if (window != null)
                    window.ExCameraChangeYaw(rot_y01);
            }
            else
            {
                rot_y01 = 0.0f;
            }

            if (Keyboard.GetKeyStates(Key.Left) == KeyStates.Down)
            {
                rot_y02 = -(float)Math.Cos(5.0f);
                if (window != null)
                    window.ExCameraChangeYaw(rot_y02);
            }
            else
            {
                rot_y02 = 0.0f;
            }

            if (Keyboard.GetKeyStates(Key.Up) == KeyStates.Down)
            {
                rot_x01 = -(float)Math.Cos(5.0f);
                if (window != null)
                    window.ExCameraChangePitch(rot_x01);
            }
            else
            {
                rot_x01 = 0.0f;
            }

            if (Keyboard.GetKeyStates(Key.Down) == KeyStates.Down)
            {
                rot_x02 = (float)Math.Cos(5.0f);
                if (window != null)
                    window.ExCameraChangePitch(rot_x02);
            }
            else
            {
                rot_x02 = 0.0f;
            }

            if (window != null)
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
            if (window != null)
                window.Hide();
        }

        private void OnLoad()
        {

            if(window == null)
            {
                this.SpherePanel.Visibility = Visibility.Visible;
                this.CubePanel.Visibility = Visibility.Collapsed;
                this.CylinderPanel.Visibility = Visibility.Collapsed;
                
                window = new DirectX.MainWindow();
                window.Owner = Window.GetWindow(this);

                this.SphereRadioButton.IsChecked = true;
                this.CubeRadioButton.IsChecked = false;
                this.CylinderRadioButton.IsChecked = false;

                cube_size_x = 10.0f;
                cube_size_y = 10.0f;
                cube_size_z = 10.0f;
                cylinder_diameter = 5.0f;
                cylinder_height = 10.0f;
                cylinder_tessellatiion = 28;
                sphere_diameter = 10.0f;
                sphere_tessellation = 30;
            }

            window.Show();
            
            if(SphereRadioButton.IsChecked == true)
                window.ExCreateSphere(sphere_diameter, sphere_tessellation);
            if (CubeRadioButton.IsChecked == true)
                window.ExCreateCube(cube_size_x, cube_size_y, cube_size_z);
            if (CylinderRadioButton.IsChecked == true)
                window.ExCreateCylinder(cylinder_height, cylinder_diameter, cylinder_tessellatiion);

            if (window != null)
                window.ExInitCamera(0.0f, 0.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        }

        private void SphereChecked(object sender, RoutedEventArgs e)
        {
            this.SpherePanel.Visibility = Visibility.Visible;
            this.SphereRadioButton.IsChecked = true;
            OnLoad();
        }

        private void SphereUnchecked(object sender, RoutedEventArgs e)
        {
            this.SpherePanel.Visibility = Visibility.Collapsed;
            this.SphereRadioButton.IsChecked = false;
        }

        private void CubeChecked(object sender, RoutedEventArgs e)
        {
            this.CubePanel.Visibility = Visibility.Visible;
            this.CubeRadioButton.IsChecked = true;
            OnLoad();
        }

        private void CubeUnchecked(object sender, RoutedEventArgs e)
        {
            this.CubePanel.Visibility = Visibility.Collapsed;
            this.CubeRadioButton.IsChecked = false;
        }

        private void CylinderChecked(object sender, RoutedEventArgs e)
        {
            this.CylinderPanel.Visibility = Visibility.Visible;
            this.CylinderRadioButton.IsChecked = true;
            OnLoad();
        }

        private void CylinderUnchecked(object sender, RoutedEventArgs e)
        {
            this.CylinderPanel.Visibility = Visibility.Collapsed;
            this.CylinderRadioButton.IsChecked = false;
        }

        private void SphereDiameterChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            sphere_diameter = (float)d.Value;

            if (window != null)
                window.ExSetSphere(sphere_diameter, sphere_tessellation);
        }

        private void SphereTessellationChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            IntegerUpDown d = (IntegerUpDown)sender;

            sphere_tessellation = (uint)d.Value;

            if (window != null)
                window.ExSetSphere(sphere_diameter, sphere_tessellation);
        }

        private void CubeWidthChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            cube_size_x = (float)d.Value;

            if (window != null)
                window.ExSetCube(cube_size_x, cube_size_y, cube_size_z);
        }

        private void CubeHeightChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            cube_size_y = (float)d.Value;

            if (window != null)
                window.ExSetCube(cube_size_x, cube_size_y, cube_size_z);
        }

        private void CubeDepthChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            cube_size_z = (float)d.Value;

            if (window != null)
                window.ExSetCube(cube_size_x, cube_size_y, cube_size_z);
        }

        private void CylinderHeightChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            cylinder_height = (float)d.Value;

            if (window != null)
                window.ExSetCylinder(cylinder_height, cylinder_diameter, cylinder_tessellatiion);
        }

        private void CylinderDiameterChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            cylinder_diameter = (float)d.Value;

            if (window != null)
                window.ExSetCylinder(cylinder_height, cylinder_diameter, cylinder_tessellatiion);
        }

        private void CylinderTessellationChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            IntegerUpDown d = (IntegerUpDown)sender;

            cylinder_tessellatiion = (uint)d.Value;

            if (window != null)
                window.ExSetCylinder(cylinder_height, cylinder_diameter, cylinder_tessellatiion);
        }
    }
}
