using System.Collections.Generic;

namespace Frontend.Core.Configuration
{
    public interface IConfiguration
    {
        IReadOnlyCollection<ConverterConfiguration> Converters { get; }
    }
}