using System;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Net.Mime;
using System.Windows;
using System.Windows.Threading;
using Caliburn.Micro;
using Action = System.Action;
using Frontend.Logging.Logging;
using Frontend.Wizard.Commands;

namespace Frontend.Wizard.Infrastructure.Log
{
    public class LogViewModel : ViewModelBase
    {
        private ObservableCollection<LogEntry> logEntries;
        private OpenUriCommand openUriCommand;

        public LogViewModel(IEventAggregator eventAggregator)
            : base(eventAggregator)
        {
            EventAggregator.Subscribe(this);
        }

        public OpenUriCommand OpenUriCommand
        {
            get { return openUriCommand ?? (openUriCommand = new OpenUriCommand(EventAggregator)); }
        }

        public ObservableCollection<LogEntry> LogEntries
        {
            get { return logEntries ?? (logEntries = new ObservableCollection<LogEntry>()); }
        }

        public void Handle(LogEntry message)
        {
            MarshallMethod(() => LogEntries.Add(message), DispatcherPriority.Send);
        }

        protected override void OnLoading(object parameter)
        {
            EventAggregator.Subscribe(this);
        }

        protected override void OnLoaded(object parameter)
        {
            base.OnLoaded(parameter);

            LogEntries.CollectionChanged += LogEntries_CollectionChanged;
        }

        private void LogEntries_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
        }

        /// <summary>
        ///     Marshalls the method.
        /// </summary>
        /// <param name="action">The action.</param>
        /// <param name="priority">The priority.</param>
        private void MarshallMethod(Action action, DispatcherPriority priority)
        {
            if (!Application.Current.Dispatcher.CheckAccess())
            {
                Application.Current.Dispatcher.Invoke(action, priority);
                return;
            }

            action();
        }
    }
}
