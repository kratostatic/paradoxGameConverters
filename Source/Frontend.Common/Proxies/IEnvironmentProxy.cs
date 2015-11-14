namespace Frontend.Common.Proxies
{
    public interface IEnvironmentProxy
    {
        string GetFrontendWorkingDirectory();
        string GetUsersFolder();
    }
}