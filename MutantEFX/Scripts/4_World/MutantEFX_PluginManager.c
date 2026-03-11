modded class PluginManager
{
    override void Init()
    {
        super.Init();
        RegisterPlugin("MutantEFX_ClientPlugin", true, false);
    }
}