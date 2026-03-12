modded class ZombieBase
{
    void ZombieBase()
    {
        if (GetGame().IsServer())
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(MutantEFX_Register, 1000, false);
    }

    private void MutantEFX_Register()
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

modded class ZombieMaleBase
{
    void ZombieMaleBase()
    {
        if (GetGame().IsServer())
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(MutantEFX_Register, 1000, false);
    }

    private void MutantEFX_Register()
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

modded class ZombieFemaleBase
{
    void ZombieFemaleBase()
    {
        if (GetGame().IsServer())
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(MutantEFX_Register, 1000, false);
    }

    private void MutantEFX_Register()
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
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(MutantEFX_Register, 1000, false);
    }

    private void MutantEFX_Register()
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