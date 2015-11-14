using System.IO.Compression;

namespace Frontend.Infrastructure.Proxies.IO
{
    public interface IZipFileProxy
    {
        void ExtractToDirectory(string sourceArchiveFileName, string destinationDirectoryName);
        void ExtractToFile(ZipArchiveEntry source, string destinationFileName, bool overwrite);
        ZipArchive Open(string archiveFileName, ZipArchiveMode mode);
    }
}