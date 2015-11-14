namespace Frontend.Core.Configuration
{
    public class ConfigurationFile
    {
        public ConfigurationFile(string path)
        {
            Path = path;
        }

        public string Path { get; }
    }
}