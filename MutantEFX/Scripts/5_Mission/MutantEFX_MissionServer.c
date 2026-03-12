modded class MissionServer
{
    override void OnInit()
    {
        MutantEFX_Config.Get();
        MutantEFX_Manager.Get();
        super.OnInit();
    }
}