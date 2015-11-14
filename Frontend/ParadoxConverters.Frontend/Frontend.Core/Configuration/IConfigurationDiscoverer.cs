using System.Collections.Generic;

namespace Frontend.Core.Configuration
{
    public interface IConfigurationDiscoverer
    {
        IEnumerable<ConverterConfiguration> DiscoverConfigurations();
    }
}