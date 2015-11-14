using System.ComponentModel;

namespace Frontend.Wizard.Infrastructure
{
    public interface IViewModelBase : INotifyPropertyChanged
    {
        void Load(object parameter);
        void Unload();
    }
}