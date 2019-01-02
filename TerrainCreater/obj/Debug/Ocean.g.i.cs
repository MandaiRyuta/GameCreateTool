﻿#pragma checksum "..\..\Ocean.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "6C34825672F68D2F7182396C32CFD310CE25512E"
//------------------------------------------------------------------------------
// <auto-generated>
//     このコードはツールによって生成されました。
//     ランタイム バージョン:4.0.30319.42000
//
//     このファイルへの変更は、以下の状況下で不正な動作の原因になったり、
//     コードが再生成されるときに損失したりします。
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using TerrainCreater;
using Xceed.Wpf.Toolkit;
using Xceed.Wpf.Toolkit.Chromes;
using Xceed.Wpf.Toolkit.Core.Converters;
using Xceed.Wpf.Toolkit.Core.Input;
using Xceed.Wpf.Toolkit.Core.Media;
using Xceed.Wpf.Toolkit.Core.Utilities;
using Xceed.Wpf.Toolkit.Panels;
using Xceed.Wpf.Toolkit.Primitives;
using Xceed.Wpf.Toolkit.PropertyGrid;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using Xceed.Wpf.Toolkit.PropertyGrid.Commands;
using Xceed.Wpf.Toolkit.PropertyGrid.Converters;
using Xceed.Wpf.Toolkit.PropertyGrid.Editors;
using Xceed.Wpf.Toolkit.Zoombox;


namespace TerrainCreater {
    
    
    /// <summary>
    /// Ocean
    /// </summary>
    public partial class Ocean : System.Windows.Controls.UserControl, System.Windows.Markup.IComponentConnector {
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/TerrainCreater;component/ocean.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\Ocean.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            
            #line 15 "..\..\Ocean.xaml"
            ((Xceed.Wpf.Toolkit.IntegerUpDown)(target)).ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<object>(this.TextureWidthChanged);
            
            #line default
            #line hidden
            return;
            case 2:
            
            #line 19 "..\..\Ocean.xaml"
            ((Xceed.Wpf.Toolkit.IntegerUpDown)(target)).ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<object>(this.TextureHeightChanged);
            
            #line default
            #line hidden
            return;
            case 3:
            
            #line 23 "..\..\Ocean.xaml"
            ((Xceed.Wpf.Toolkit.DoubleUpDown)(target)).ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<object>(this.TimeChanged);
            
            #line default
            #line hidden
            return;
            case 4:
            
            #line 27 "..\..\Ocean.xaml"
            ((Xceed.Wpf.Toolkit.DoubleUpDown)(target)).ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<object>(this.MinDistanceChanged);
            
            #line default
            #line hidden
            return;
            case 5:
            
            #line 31 "..\..\Ocean.xaml"
            ((Xceed.Wpf.Toolkit.DoubleUpDown)(target)).ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<object>(this.MaxDistanceChanged);
            
            #line default
            #line hidden
            return;
            case 6:
            
            #line 35 "..\..\Ocean.xaml"
            ((Xceed.Wpf.Toolkit.DoubleUpDown)(target)).ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<object>(this.MinLog2TessChanged);
            
            #line default
            #line hidden
            return;
            case 7:
            
            #line 39 "..\..\Ocean.xaml"
            ((Xceed.Wpf.Toolkit.DoubleUpDown)(target)).ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<object>(this.MaxLog2TessChanged);
            
            #line default
            #line hidden
            return;
            case 8:
            
            #line 44 "..\..\Ocean.xaml"
            ((System.Windows.Controls.CheckBox)(target)).Checked += new System.Windows.RoutedEventHandler(this.DrawWiresTrue);
            
            #line default
            #line hidden
            
            #line 44 "..\..\Ocean.xaml"
            ((System.Windows.Controls.CheckBox)(target)).Unchecked += new System.Windows.RoutedEventHandler(this.DrawWiresFalse);
            
            #line default
            #line hidden
            return;
            case 9:
            
            #line 50 "..\..\Ocean.xaml"
            ((System.Windows.Controls.CheckBox)(target)).Checked += new System.Windows.RoutedEventHandler(this.DrawNormalTrue);
            
            #line default
            #line hidden
            
            #line 50 "..\..\Ocean.xaml"
            ((System.Windows.Controls.CheckBox)(target)).Unchecked += new System.Windows.RoutedEventHandler(this.DrawNormalFalse);
            
            #line default
            #line hidden
            return;
            case 10:
            
            #line 56 "..\..\Ocean.xaml"
            ((System.Windows.Controls.CheckBox)(target)).Checked += new System.Windows.RoutedEventHandler(this.ApplyAngleCorrectionTrue);
            
            #line default
            #line hidden
            
            #line 56 "..\..\Ocean.xaml"
            ((System.Windows.Controls.CheckBox)(target)).Unchecked += new System.Windows.RoutedEventHandler(this.ApplyAngleCorrectionFalse);
            
            #line default
            #line hidden
            return;
            case 11:
            
            #line 62 "..\..\Ocean.xaml"
            ((System.Windows.Controls.CheckBox)(target)).Checked += new System.Windows.RoutedEventHandler(this.HoldTrue);
            
            #line default
            #line hidden
            
            #line 62 "..\..\Ocean.xaml"
            ((System.Windows.Controls.CheckBox)(target)).Unchecked += new System.Windows.RoutedEventHandler(this.HoldFalse);
            
            #line default
            #line hidden
            return;
            case 12:
            
            #line 67 "..\..\Ocean.xaml"
            ((Xceed.Wpf.Toolkit.DoubleUpDown)(target)).ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<object>(this.SizeTerrainChanged);
            
            #line default
            #line hidden
            return;
            case 13:
            
            #line 71 "..\..\Ocean.xaml"
            ((Xceed.Wpf.Toolkit.IntegerUpDown)(target)).ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<object>(this.SqrtNumberOfPatchsChanged);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}
