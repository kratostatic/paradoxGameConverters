using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Frontend.Core.Configuration
{
    public class Configuration : IConfiguration
    {
        public Configuration(IConfigurationDiscoverer configurationDiscoverer)
        {
            Converters = new ReadOnlyCollection<ConverterConfiguration>(configurationDiscoverer.DiscoverConfigurations().ToList());
        }

        public IReadOnlyCollection<ConverterConfiguration> Converters { get; private set; }
    }
}
