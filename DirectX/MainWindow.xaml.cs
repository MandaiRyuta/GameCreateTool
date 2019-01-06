using System;
using System.Collections.Generic;
using System.Diagnostics;
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
        private extern static void Reset(IntPtr hwnd, int size_x, int size_y);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Run();

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CreateTerrain(uint div_x, uint div_y, float frequency, float height, float size_x, float size_y);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CreateCube(float size_x, float size_y, float size_z);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CreateSphere(float diameter, uint tessellation);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CreateCylinder(float height, float diameter, uint tessellation);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CreateOcean(uint texture_width, uint texture_height, float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor, bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, uint sqrt_number_of_patchs);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void SetTerrain(uint div_x, uint div_y, float frequency, float height, float size_x, float size_y);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void SetCube(float size_x, float size_y, float size_z);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void SetSphere(float diameter, uint tessellation);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void SetCylinder(float height, float diameter, uint tessellation);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void SetOcean(uint texture_width, uint texture_height, float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor, bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, uint sqrt_number_of_patchs);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void DefaultSetView(float eye_x, float eye_y, float eye_z, float at_x, float at_y, float at_z, float up_x, float up_y, float up_z);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CameraInit(float eye_x, float eye_y, float eye_z, float at_x, float at_y, float at_z, float up_x, float up_y, float up_z);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CameraChangePitch(float move_amount);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CameraChangeYaw(float move_amount);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CameraChangeSide(float move_amount);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CameraChangeUpDown(float move_amount);

        [DllImport("exporter.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CameraUpdate();

        

        private DispatcherTimer dispatcherTimer = null;

        
        public MainWindow()
        {
            InitializeComponent();
            
            this.MouseLeftButtonDown += (sender, e) => this.DragMove();

            Loaded += (s, e) => OnLoad();

            IsVisibleChanged += (s, e) => ONUnLoad();
        }

        private void ONUnLoad()
        {
            if (IsVisible != false)
            {
                HwndSource source = (HwndSource)HwndSource.FromVisual(this);

                IntPtr handle = source.Handle;

                Initialize(handle, 1280, 720);

                if (dispatcherTimer == null)
                {
                    dispatcherTimer = new DispatcherTimer();
                    dispatcherTimer.Tick += new EventHandler(Run);
                    dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 1000 / 60);
                    dispatcherTimer.Start();
                }
            }
            else
            {
                if (dispatcherTimer != null)
                {
                    dispatcherTimer.Stop();
                    dispatcherTimer = null;
                }
            }
        }

        private void Run(object sender, EventArgs e)
        {
            if (dispatcherTimer != null)
            {
                Run();
            }
        }

        private void OnLoad()
        {
            HwndSource source = (HwndSource)HwndSource.FromVisual(this);

            IntPtr handle = source.Handle;

            Initialize(handle, 1280, 720);

            if (dispatcherTimer == null)
            {
                dispatcherTimer = new DispatcherTimer();
                dispatcherTimer.Tick += new EventHandler(Run);
                dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 1000 / 60);
                dispatcherTimer.Start();
            }
        }

        public void ExCreateTerrain(uint div_x, uint div_y, float frequency, float height, float size_x, float size_y)
        {
            CreateTerrain(div_x, div_y, frequency, height, size_x, size_y);
        }

        public void ExCreateCube(float size_x, float size_y, float size_z)
        {
            CreateCube(size_x, size_y, size_z);
        }

        public void ExCreateSphere(float diameter, uint tessellation)
        {
            CreateSphere(diameter, tessellation);
        }

        public void ExCreateCylinder(float height, float diameter, uint tessellation)
        {
            CreateCylinder(height, diameter, tessellation);
        }

        public void ExCreateOcean(uint texture_width, uint texture_height, float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor, bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, uint sqrt_number_of_patchs)
        {
            CreateOcean(texture_width, texture_height, time, min_distance, max_distance, min_log2tessfactor, max_log2tessfactor, draw_wires, draw_normal, apply_anglecorrection, hold, size_terrain, sqrt_number_of_patchs);
        }

        public void ExSetTerrain(uint div_x, uint div_y, float frequency, float height, float size_x, float size_y)
        {
            SetTerrain(div_x, div_y, frequency, height, size_x, size_y);
        }

        public void ExSetCube(float size_x, float size_y, float size_z)
        {
            SetCube(size_x, size_y, size_z);
        }

        public void ExSetSphere(float diameter, uint tessellation)
        {
            SetSphere(diameter, tessellation);
        }

        public void ExSetCylinder(float height, float diameter, uint tessellation)
        {
            SetCylinder(height, diameter, tessellation);
        }

        public void ExSetOcean(uint texture_width, uint texture_height, float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor, bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, uint sqrt_number_of_patchs)
        {
            SetOcean(texture_width, texture_height, time, min_distance, max_distance, min_log2tessfactor, max_log2tessfactor, draw_wires, draw_normal, apply_anglecorrection, hold, size_terrain, sqrt_number_of_patchs);
        }

        public void ExDefaultSetView(float eye_x, float eye_y, float eye_z, float at_x, float at_y, float at_z, float up_x, float up_y, float up_z)
        {
            DefaultSetView(eye_x, eye_y, eye_z, at_x, at_y, at_z, up_x, up_y, up_z);
        }

        public void ExInitCamera(float eye_x, float eye_y, float eye_z, float at_x, float at_y, float at_z, float up_x, float up_y, float up_z)
        {
            CameraInit(eye_x, eye_y, eye_z, at_x, at_y, at_z, up_x, up_y, up_z);
        }

        public void ExCameraUpdate()
        {
            CameraUpdate();
        }

        public void ExCameraChangeYaw(float move_amount)
        {
            CameraChangeYaw(move_amount);
        }

        public void ExCameraChangePitch(float move_amount)
        {
            CameraChangePitch(move_amount);
        }

        public void ExCameraChangeSide(float move_amount)
        {
            CameraChangeSide(move_amount);
        }

        public void ExCameraChangeUpDown(float move_amount)
        {
            CameraChangeUpDown(move_amount);
        }
        
    }
}
