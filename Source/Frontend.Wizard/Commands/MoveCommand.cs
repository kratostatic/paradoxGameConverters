using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Caliburn.Micro;
using Frontend.Core.ViewModels;
using Frontend.Infrastructure.Commands;
using Frontend.Wizard.Infrastructure;

namespace Frontend.Wizard.Commands
{
    public class MoveCommand : CommandBase
    {
        private readonly StepConductorBase conductorViewModel;

        public MoveCommand(IEventAggregator eventAggregator, StepConductorBase conductorViewModel)
            : base(eventAggregator)
        {
            this.conductorViewModel = conductorViewModel;
        }

        protected override bool OnCanExecute(object parameter)
        {
            switch ((Direction) parameter)
            {
                case Direction.Backward:
                    return conductorViewModel.CanMoveBackward;

                case Direction.Forward:
                    return conductorViewModel.CanMoveForward;
            }

            return false;
        }

        protected override void OnExecute(object parameter)
        {
            conductorViewModel.Move((Direction) parameter);
        }
    }
}
