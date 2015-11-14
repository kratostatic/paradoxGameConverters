namespace Frontend.Infrastructure.Helpers.IO
{
    public interface IDirectoryHelper
    {
        string[] GetDirectories(string path);
        string[] GetDirectories(string path, string searchPattern);
    }
}