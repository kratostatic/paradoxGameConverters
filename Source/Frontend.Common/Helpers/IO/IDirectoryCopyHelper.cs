namespace Frontend.Infrastructure.Helpers.IO
{
    public interface IDirectoryCopyHelper
    {
        void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs, bool overwrite);
    }
}