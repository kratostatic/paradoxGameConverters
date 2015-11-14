using System;
using System.ComponentModel;
using System.Linq.Expressions;
using Caliburn.Micro;

namespace Frontend.Wizard.Infrastructure
{
    public abstract class ViewModelBase : PropertyChangedBase, IDisposable, IViewModelBase
    {
        private bool _isDisposed;

        protected ViewModelBase(IEventAggregator eventAggregator)
        {
            EventAggregator = eventAggregator;

            //HACK: This needs rethinking, but when vms gets resolved from a view (Say, a contentcontrol binding to a vm), 
            //the Load method obviously won't get called.
            //this.Load(null);
        }

        protected IEventAggregator EventAggregator { get; private set; }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        public void Load(object parameter)
        {
            OnLoading(parameter);
            OnLoad(parameter);
            OnLoaded(parameter);
        }

        public void Unload()
        {
            OnUnloading();
            OnUnload();
            OnUnloaded();
        }

        protected virtual void Dispose(bool isDisposing)
        {
            if (!isDisposing || _isDisposed)
            {
                return;
            }

            Unload();
            _isDisposed = true;
        }

        protected virtual void OnLoading(object parameter)
        {
        }

        protected virtual void OnLoad(object parameter)
        {
        }

        protected virtual void OnLoaded(object parameter)
        {
        }

        protected virtual void OnUnloading()
        {
        }

        protected virtual void OnUnload()
        {
        }

        protected virtual void OnUnloaded()
        {
        }
    }
}