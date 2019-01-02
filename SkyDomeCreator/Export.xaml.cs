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
using Xceed.Wpf.Toolkit;

namespace SkyDomeCreator
{
    /// <summary>
    /// Export.xaml の相互作用ロジック
    /// </summary>

    public partial class Export : UserControl
    {
        DirectX.MainWindow window = null;

        float cube_size_x;
        float cube_size_y;
        float cube_size_z;
        float cylinder_height;
        float cylinder_diameter;
        uint cylinder_tessellatiion;
        float sphere_diameter;
        uint sphere_tessellation;

        public Export()
        {
            InitializeComponent();

            Loaded += (s, e) => OnLoad();

            Unloaded += (s, e) => OnUnLoad();
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
                this.SpherePanel.Visibility = Visibility.Collapsed;
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
            
            window.ExDefaultSetView();

            if(SphereRadioButton.IsChecked == true)
                window.ExCreateSphere(sphere_diameter, sphere_tessellation);
            if (CubeRadioButton.IsChecked == true)
                window.ExCreateCube(cube_size_x, cube_size_y, cube_size_z);
            if (CylinderRadioButton.IsChecked == true)
                window.ExCreateCylinder(cylinder_height, cylinder_diameter, cylinder_tessellatiion);
        }

        private void SphereChecked(object sender, RoutedEventArgs e)
        {
            this.SpherePanel.Visibility = Visibility.Visible;

            if (window != null)
                window.ExCreateSphere(sphere_diameter, sphere_tessellation);
        }

        private void SphereUnchecked(object sender, RoutedEventArgs e)
        {
            this.SpherePanel.Visibility = Visibility.Collapsed;
        }

        private void CubeChecked(object sender, RoutedEventArgs e)
        {
            this.CubePanel.Visibility = Visibility.Visible;

            if (window != null)
                window.ExCreateCube(cube_size_x, cube_size_y, cube_size_z);
        }

        private void CubeUnchecked(object sender, RoutedEventArgs e)
        {
            this.CubePanel.Visibility = Visibility.Collapsed;
        }

        private void CylinderChecked(object sender, RoutedEventArgs e)
        {
            this.CylinderPanel.Visibility = Visibility.Visible;

            if (window != null)
                window.ExCreateCylinder(cylinder_height, cylinder_diameter, cylinder_tessellatiion);
        }

        private void CylinderUnchecked(object sender, RoutedEventArgs e)
        {
            this.CylinderPanel.Visibility = Visibility.Collapsed;
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
