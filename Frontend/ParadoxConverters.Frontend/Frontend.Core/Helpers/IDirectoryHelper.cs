using Frontend.Core.Model.Interfaces;

namespace Frontend.Core.Helpers
{
    public interface IDirectoryHelper
    {
        string GetConverterWorkingDirectory(IConverterSettings currentConverter);
        string[] GetDirectories(string path);
        string[] GetDirectories(string path, string searchPattern);
    }
}