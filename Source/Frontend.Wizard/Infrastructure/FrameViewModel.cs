using System.Collections.Generic;
using System.Windows.Input;
using Caliburn.Micro;
using Frontend.Wizard.Commands;
using Frontend.Wizard.Events;
using Frontend.Wizard.Infrastructure;
using Frontend.Wizard.Infrastructure.Log;

namespace Frontend.Core.ViewModels
{
    public class FrameViewModel : StepConductorBase
    {
        public FrameViewModel(IEventAggregator eventAggregator)
            : base(eventAggregator)
        {
            EventAggregator.Subscribe(this);
        }

        public void Handle(PreferenceStepOperationArgs message)
        {
            switch (message.Operation)
            {
                case PreferenceOperation.AddSteps:
                    AddPreferenceSteps(message.NewSteps);
                    break;

                case PreferenceOperation.Clear:
                    RemoveConverterSpecificSteps();
                    break;
            }
        }

        private void AddPreferenceSteps(IList<IStep> newSteps)
        {
            foreach (var step in newSteps)
            {
                Steps.Add(step);
            }
        }

        private void RemoveConverterSpecificSteps()
        {
            var removedCount = 0;

            // Assumption: The first two steps are:
            // * The welcome view
            // * The path picker view
            // So we remove everything else.
            while (Steps.Count > 2)
            {
                Steps.RemoveAt(2);
                removedCount++;
            }
        }

        #region [ Fields ]

        private LogViewModel logViewModel;
        private ICommand moveCommand;

        #endregion

        #region [ Properties ]

        public LogViewModel Log
        {
            get { return logViewModel ?? (logViewModel = new LogViewModel(EventAggregator)); }
        }

        public ICommand MoveCommand
        {
            get { return moveCommand ?? (moveCommand = new MoveCommand(EventAggregator, this)); }
        }

        #endregion
    }
}