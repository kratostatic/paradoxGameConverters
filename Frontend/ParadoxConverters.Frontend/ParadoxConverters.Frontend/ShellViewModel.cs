using System;
using Caliburn.Micro;
using Frontend.Core.Navigation;
using Frontend.Core.ViewModels;
using Frontend.Core.ViewModels.Interfaces;

namespace Frontend.Client
{
    public class ShellViewModel : IShell, IDisposable
    {
        private readonly IEventAggregator eventAggregator;
        private readonly IWelcomeViewModel _welcomeViewModel;
        private readonly IPathPickerViewModel _pathPickerViewModel;
        private FrameViewModel frameViewModel;
        private bool isDisposed;

        public ShellViewModel(IEventAggregator eventAggregator, IWelcomeViewModel welcomeViewModel, IPathPickerViewModel pathPickerViewModel)
        {
            this.eventAggregator = eventAggregator;
            _welcomeViewModel = welcomeViewModel;
            _pathPickerViewModel = pathPickerViewModel;
        }

        public FrameViewModel FrameViewModel
        {
            get
            {
                if (frameViewModel == null)
                {
                    frameViewModel = new FrameViewModel(eventAggregator);

                    frameViewModel.Steps.Add(_welcomeViewModel);
                    frameViewModel.Steps.Add(_pathPickerViewModel);

                    FrameViewModel.Move(Direction.Forward);
                }

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
            if (isDisposing && !isDisposed)
            {
                frameViewModel.Dispose();
                isDisposed = true;
            }
        }
    }
}