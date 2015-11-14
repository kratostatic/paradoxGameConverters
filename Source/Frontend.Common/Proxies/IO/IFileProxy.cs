using System.Collections.Generic;

namespace Frontend.Infrastructure.Proxies.IO
{
    public interface IFileProxy
    {
        bool Exists(string path);
        IEnumerable<string> ExistsMany(IEnumerable<string> paths);
        void Copy(string sourceFileName, string destFileName, bool overwrite);
        void WriteAllText(string path, string contents);
        string ReadAllText(string path);
        void DeleteFile(string path);
    }
}