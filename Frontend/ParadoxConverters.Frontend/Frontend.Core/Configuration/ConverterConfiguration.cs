namespace Frontend.Core.Configuration
{
    public class ConverterConfiguration
    {
        public ConverterConfiguration(ConfigurationFile configurationFile)
        {
            ConfigurationFile = configurationFile;
        }

        public ConfigurationFile ConfigurationFile { get; }
    }
}