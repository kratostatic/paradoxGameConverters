using System.Collections.Generic;
using System.IO;
using System.Linq;
using Frontend.Core.Common.Proxies;
using Frontend.Core.Helpers;

namespace Frontend.Core.Configuration
{
    public class ConfigurationDiscoverer : IConfigurationDiscoverer
    {
        private const string ExpectedConfigurationDirectoryName = "configuration";
        private const string ExpectedConfigurationFileName = "configuration.xml";
        private readonly IDirectoryHelper _directoryHelper;
        private readonly IEnvironmentProxy _environmentProxy;
        private readonly IFolderProxy _folderProxy;
        private readonly IFileProxy _fileProxy;

        public ConfigurationDiscoverer(IEnvironmentProxy environmentProxy, IDirectoryHelper directoryHelper,
            IFolderProxy folderProxy, IFileProxy fileProxy)
        {
            _environmentProxy = environmentProxy;
            _directoryHelper = directoryHelper;
            _folderProxy = folderProxy;
            _fileProxy = fileProxy;
        }

        public IEnumerable<ConverterConfiguration> DiscoverConfigurations()
        {
            var currentDirectory = _environmentProxy.GetFrontendWorkingDirectory();

            var subDirectories = _directoryHelper.GetDirectories(currentDirectory);
            
            var foundConverters = new List<ConverterConfiguration>();

            foreach (var subDirectory in subDirectories.ToList())
            {
                var subSubDirectories = _directoryHelper.GetDirectories(subDirectory, ExpectedConfigurationDirectoryName);

                foreach (var subSubDirectory in subSubDirectories)
                {
                    var configurationFile = GetConfigurationFile(subSubDirectory);

                    if (string.IsNullOrEmpty(configurationFile))
                    {
                        continue;
                    }

                    foundConverters.Add(new ConverterConfiguration(new ConfigurationFile(configurationFile)));
                }
            }

            return foundConverters;
        }

        private string GetConfigurationFile(string subDirectory)
        {
            var expectedFilePath = Path.Combine(subDirectory, ExpectedConfigurationFileName);
            if (!_folderProxy.Exists(subDirectory) || !_fileProxy.Exists(expectedFilePath))
            {
                return string.Empty;
            }

            return expectedFilePath;
        }
    }
}