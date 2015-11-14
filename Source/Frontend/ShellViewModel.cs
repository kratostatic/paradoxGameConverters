using System;
using Caliburn.Micro;
using Frontend.Core.ViewModels;
using Frontend.Wizard.Infrastructure;

namespace Frontend.Client
{
    public class ShellViewModel : IShell, IDisposable
    {
        private readonly IEventAggregator _eventAggregator;
        private FrameViewModel frameViewModel;
        private bool _isDisposed;

        public ShellViewModel(IEventAggregator eventAggregator)
        {
            this._eventAggregator = eventAggregator;
        }

        public FrameViewModel FrameViewModel
        {
            get
            {
                if (frameViewModel != null)
                {
                    return frameViewModel;
                }

                frameViewModel = new FrameViewModel(_eventAggregator);
                    
                FrameViewModel.Move(Direction.Forward);

                return frameViewModel;
            }
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool isDisposing)
        {
            if (!isDisposing || _isDisposed)
            {
                return;
            }

            frameViewModel.Dispose();
            _isDisposed = true;
        }
    }
}