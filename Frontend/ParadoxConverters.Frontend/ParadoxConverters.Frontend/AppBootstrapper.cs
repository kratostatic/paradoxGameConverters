using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Windows;
using System.Windows.Threading;
using Caliburn.Micro;
using Frontend.Core.Common.Proxies;
using Frontend.Core.Configuration;
using Frontend.Core.Factories;
using Frontend.Core.Helpers;
using Frontend.Core.Logging;
using Frontend.Core.Model;
using Frontend.Core.Model.Interfaces;
using Frontend.Core.ViewModels;
using Frontend.Core.ViewModels.Interfaces;

namespace Frontend.Client
{
    /// <summary>
    /// The AppBootStrapper is responsible for configuring and setting everything up, before displaying the first view.
    /// </summary>
    public sealed class AppBootstrapper : BootstrapperBase
    {
        private SimpleContainer _container;

        public AppBootstrapper()
        {
            StartRuntime();
        }
        
        protected override void Configure()
        {
            _container = new SimpleContainer();

            // Helpers
            _container.Singleton<IEnvironmentProxy, EnvironmentProxy>();
            _container.Singleton<IDirectoryHelper, DirectoryHelper>();
            _container.Singleton<IDirectoryCopyHelper, DirectoryCopyHelper>();
            _container.Singleton<IFileProxy, FileProxy>();
            _container.Singleton<IFolderProxy, FolderProxy>();
            
            // Infrastructure
            _container.Singleton<IWindowManager, WindowManager>();
            _container.Singleton<IEventAggregator, EventAggregator>();

            // Configuration
            _container.Singleton<IConfigurationDiscoverer, ConfigurationDiscoverer>();
            _container.Singleton<IConfiguration, Configuration>();
            _container.Singleton<IConfigurationFactory, ConfigurationFactory>();
            _container.Singleton<IConverterSettingsFactory, ConverterSettingsFactory>();

            // View models
            _container.PerRequest<IShell, ShellViewModel>();
            _container.PerRequest<IFrameViewModel, FrameViewModel>();
            _container.PerRequest<IWelcomeViewModel, WelcomeViewModel>();
            _container.PerRequest<IPathPickerViewModel, PathPickerViewModel>();
        }

        protected override object GetInstance(Type service, string key)
        {
            var instance = _container.GetInstance(service, key);
            if (instance != null)
            {
                return instance;
            }

            throw new InvalidOperationException("Could not locate any instances.");
        }

        protected override IEnumerable<Assembly> SelectAssemblies()
        {
            var assemblies = base.SelectAssemblies().ToList();

            // This includes the Frontend.Core assembly.
            assemblies.Add(Assembly.GetAssembly(typeof (FrameViewModel)));

            return assemblies;
        }

        protected override IEnumerable<object> GetAllInstances(Type service)
        {
            return _container.GetAllInstances(service);
        }

        protected override void BuildUp(object instance)
        {
            _container.BuildUp(instance);
        }

        protected override void OnStartup(object sender, StartupEventArgs e)
        {
            DisplayRootViewFor<IShell>();
        }

        protected override void OnUnhandledException(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            var eventAggregator = this._container.GetInstance<IEventAggregator>();
            eventAggregator.PublishOnUIThread(new LogEntry("Error occured: " + e.Exception.Message,
                LogEntrySeverity.Error, LogEntrySource.UI));
        }
    }
}