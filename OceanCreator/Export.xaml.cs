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

namespace OceanCreator
{
    /// <summary>
    /// Ocean.xaml の相互作用ロジック
    /// </summary>
    public partial class Export : UserControl
    {
        DirectX.MainWindow window = null;

        private DispatcherTimer dispatchertimer;
        uint textureWidth;
        uint textureHeight;
        float time;
        float minDistance;
        float maxDistance;
        float minLog2TessFactor;
        float maxLog2TessFactor;
        bool drawWires;
        bool drawNormal;
        bool applyAnglecorrection;
        bool hold;
        float sizeTerrain;
        uint sqrtNumberOfPatchs;

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
                window = new DirectX.MainWindow();
                window.Owner = Window.GetWindow(this);

                textureWidth = 1024;
                textureHeight = 1024;
                time = 0.0f;
                minDistance = 100.0f;
                maxDistance = 1000.0f;
                minLog2TessFactor = 1.0f;
                maxLog2TessFactor = 5.0f;
                drawWires = false;
                drawNormal = false;
                applyAnglecorrection = false;
                hold = false;
                sizeTerrain = 2000.0f;
                sqrtNumberOfPatchs = 8;
            }

            window.Show();

            window.ExCreateOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);

            if (window != null)
                window.ExInitCamera(0.0f, 15.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        }

        private void TextureWidthChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            IntegerUpDown d = (IntegerUpDown)sender;

            textureWidth = (uint)d.Value;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void TextureHeightChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            IntegerUpDown d = (IntegerUpDown)sender;

            textureHeight = (uint)d.Value;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void TimeChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            time = (float)d.Value;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void MinDistanceChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            minDistance = (float)d.Value;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void MaxDistanceChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            maxDistance = (float)d.Value;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void MinLog2TessChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            minLog2TessFactor = (float)d.Value;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void MaxLog2TessChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            maxLog2TessFactor = (float)d.Value;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void SizeTerrainChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DoubleUpDown d = (DoubleUpDown)sender;

            sizeTerrain = (float)d.Value;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void SqrtNumberOfPatchsChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            IntegerUpDown d = (IntegerUpDown)sender;

            sqrtNumberOfPatchs = (uint)d.Value;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void DrawWiresTrue(object sender, RoutedEventArgs e)
        {
            drawWires = true;

            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void DrawWiresFalse(object sender, RoutedEventArgs e)
        {
            drawWires = false;

            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void DrawNormalTrue(object sender, RoutedEventArgs e)
        {
            drawNormal = true;

            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void DrawNormalFalse(object sender, RoutedEventArgs e)
        {
            drawNormal = false;

            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void ApplyAngleCorrectionTrue(object sender, RoutedEventArgs e)
        {
            applyAnglecorrection = true;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void ApplyAngleCorrectionFalse(object sender, RoutedEventArgs e)
        {
            applyAnglecorrection = false;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void HoldTrue(object sender, RoutedEventArgs e)
        {
            hold = true;

            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }

        private void HoldFalse(object sender, RoutedEventArgs e)
        {
            hold = false;
            if (window != null)
                window.ExSetOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
        }
    }
}
