modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        MutantEFX_Config.Get();
        MutantEFX_Manager.Get();
    }
}