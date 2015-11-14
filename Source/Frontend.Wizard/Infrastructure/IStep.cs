namespace Frontend.Wizard.Infrastructure
{
    public interface IStep : IViewModelBase
    {
        bool IsValid { get; }
    }
}