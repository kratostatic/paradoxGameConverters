using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Caliburn.Micro;
using Frontend.Core.Factories;
using Frontend.Core.Model;
using Frontend.Core.Model.Interfaces;

namespace Frontend.Core.Configuration
{
    public interface IConfigurationFactory
    {
        IEnumerable<ConverterSettings> BuildSettings();
    }

    public class ConfigurationFactory : IConfigurationFactory
    {
        private readonly IConfiguration _configuration;
        private readonly IConverterSettingsFactory _settingsFactory;

        public ConfigurationFactory(IConfiguration configuration, IConverterSettingsFactory settingsFactory)
        {
            _configuration = configuration;
            _settingsFactory = settingsFactory;
        }

        public IEnumerable<ConverterSettings> BuildSettings()
        {
            var settings = new List<ConverterSettings>();

            var filePaths = _configuration.Converters.Select(c => c.ConfigurationFile).Select(f => f.Path);

            filePaths.ForEach(fp => settings.AddRange(_settingsFactory.BuildModels<ConverterSettings>(fp)));

            return settings;
        }
    }
}
