using System.Windows;

namespace Frontend.Common.Proxies
{
    public class MessageBoxProxy : IMessageBoxProxy
    {
        public MessageBoxResult Show(string messageBoxText, string caption, MessageBoxButton button)
        {
            return MessageBox.Show(messageBoxText, caption, button);
        }
    }
}