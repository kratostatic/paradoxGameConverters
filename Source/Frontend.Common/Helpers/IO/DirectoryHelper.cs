using System.IO;

namespace Frontend.Infrastructure.Helpers.IO
{
    /// <summary>
    ///     Helper class that finds working directories, whether for the frontend or the various converters
    /// </summary>
    public class DirectoryHelper : IDirectoryHelper
    {
        public string[] GetDirectories(string path)
        {
            return Directory.GetDirectories(path);
        }

        public string[] GetDirectories(string path, string searchPattern)
        {
            return Directory.GetDirectories(path, searchPattern);
        }
    }
}