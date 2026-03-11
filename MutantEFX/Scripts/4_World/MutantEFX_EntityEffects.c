modded class ZombieBase
{
    void ZombieBase()
    {
        if (GetGame().IsServer())
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RegisterToMutantEFX, 1000, false);
    }

    private void RegisterToMutantEFX()
    {
        MutantEFX_Manager.Get().RegisterEntity(this);
    }

    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        if (GetGame().IsServer())
        {
            MutantEFX_Manager.Get().OnEntityDeath(this);
            MutantEFX_Manager.Get().UnregisterEntity(this);
        }
    }
}

modded class AnimalBase
{
    void AnimalBase()
    {
        if (GetGame().IsServer())
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RegisterToMutantEFX_Animal, 1000, false);
    }

    private void RegisterToMutantEFX_Animal()
    {
        MutantEFX_Manager.Get().RegisterEntity(this);
    }

    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        if (GetGame().IsServer())
        {
            MutantEFX_Manager.Get().OnEntityDeath(this);
            MutantEFX_Manager.Get().UnregisterEntity(this);
        }
    }
}