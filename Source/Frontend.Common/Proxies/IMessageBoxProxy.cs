using System.Windows;

namespace Frontend.Common.Proxies
{
    public interface IMessageBoxProxy
    {
        MessageBoxResult Show(string messageBoxText, string caption, MessageBoxButton button);
    }
}