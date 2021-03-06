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
using Xceed.Wpf.Toolkit;

namespace OceanCreator
{
    /// <summary>
    /// Ocean.xaml の相互作用ロジック
    /// </summary>
    public partial class Ocean : UserControl
    {
        DirectX.MainWindow window = null;

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

        public Ocean()
        {
            InitializeComponent();

            Loaded += (s, e) => OnLoad();
        }

        private void OnLoad()
        {
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

            window = new DirectX.MainWindow();

            window.Show();

            window.ExOceanSetView();

            window.ExCreateOcean(textureWidth, textureHeight, time, minDistance, maxDistance, minLog2TessFactor, maxLog2TessFactor, drawWires, drawNormal, applyAnglecorrection, hold, sizeTerrain, sqrtNumberOfPatchs);
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

            if(window != null)
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

            if(window != null)
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
