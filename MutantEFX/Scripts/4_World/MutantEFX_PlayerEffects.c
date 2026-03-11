modded class PlayerBase
{
    private bool  m_MutantEFX_IsBlurred        = false;
    private bool  m_MutantEFX_IsLifted         = false;
    private float m_MutantEFX_LiftShakeTimer   = 0.0;
    private int   m_MutantEFX_ShotsFired       = 0;
    private int   m_MutantEFX_ShotsTotal       = 0;
    private bool  m_MutantEFX_IsForceShooting  = false;
    private bool  m_MutantEFX_SuicideStarted   = false;

    bool MutantEFX_IsSuicideActive()
    {
        return m_MutantEFX_SuicideStarted;
    }

    void MutantEFX_StartSuicide()
    {
        if (m_MutantEFX_SuicideStarted) return;
        m_MutantEFX_SuicideStarted = true;
        SymptomBase symptom = GetSymptomManager().QueueUpPrimarySymptom(MutantEFX_SuicideSymptom.SYMPTOM_ID);
        if (symptom)
            symptom.SetDuration(7);
    }

    void MutantEFX_ResetSuicide()
    {
        m_MutantEFX_SuicideStarted = false;
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        Param1<float> pFloat;
        Param1<int>   pInt;

        switch (rpc_type)
        {
            case MutantEFX_RPCs.RPC_PSYCHIC_BLUR_ENTER:
            {
                if (ctx.Read(pFloat))
                {
                    m_MutantEFX_IsBlurred = true;
                    if (!GetGame().IsDedicatedServer())
                        PPEffects.SetBlur(pFloat.param1 * 0.25);
                }
                break;
            }
            case MutantEFX_RPCs.RPC_PSYCHIC_BLUR_EXIT:
            {
                m_MutantEFX_IsBlurred = false;
                if (!GetGame().IsDedicatedServer())
                    PPEffects.SetBlur(0.0);
                break;
            }
            case MutantEFX_RPCs.RPC_TELEKINESIS_LIFT_ENTER:
            {
                if (!GetGame().IsDedicatedServer() && ctx.Read(pFloat))
                {
                    m_MutantEFX_IsLifted       = true;
                    m_MutantEFX_LiftShakeTimer = pFloat.param1;
                }
                break;
            }
            case MutantEFX_RPCs.RPC_TELEKINESIS_LIFT_EXIT:
            {
                m_MutantEFX_IsLifted       = false;
                m_MutantEFX_LiftShakeTimer = 0.0;
                break;
            }
            case MutantEFX_RPCs.RPC_PSY_PUSH:
            {
                if (!GetGame().IsDedicatedServer())
                    PPEffects.SetBlur(0.12);
                break;
            }
            case MutantEFX_RPCs.RPC_FORCE_SHOOT:
            {
                if (ctx.Read(pInt) && !m_MutantEFX_IsForceShooting)
                {
                    m_MutantEFX_ShotsFired      = 0;
                    m_MutantEFX_ShotsTotal      = pInt.param1;
                    m_MutantEFX_IsForceShooting = true;
                    MutantEFX_PerformForceShoot();
                }
                break;
            }
            case MutantEFX_RPCs.RPC_FORCE_SUICIDE:
            {
                if (GetGame().IsServer())
                    MutantEFX_StartSuicide();
                break;
            }
            case MutantEFX_RPCs.RPC_PLAY_GUNSHOT:
            {
                if (!GetGame().IsDedicatedServer() && IsControlledPlayer())
                {
                    EffectSound shot;
                    PlaySoundSet(shot, "pistol_FiredChamber_SoundSet", 0, 0);
                }
                break;
            }
        }
    }

    override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
    {
        super.CommandHandler(pDt, pCurrentCommandID, pCurrentCommandFinished);

        if (GetGame().IsDedicatedServer())
            return;
        if (!IsControlledPlayer())
            return;

        if (m_MutantEFX_IsLifted)
        {
            m_MutantEFX_LiftShakeTimer -= pDt;
            DayZPlayerImplementAiming aim = GetAimingModel();
            if (aim)
                aim.SetCamShakeValues(Math.RandomFloat(-0.08, 0.08), Math.RandomFloat(-0.06, 0.06));

            if (m_MutantEFX_LiftShakeTimer <= 0.0)
            {
                m_MutantEFX_IsLifted       = false;
                m_MutantEFX_LiftShakeTimer = 0.0;
                DayZPlayerImplementAiming aimStop = GetAimingModel();
                if (aimStop)
                    aimStop.SetCamShakeValues(0.0, 0.0);
            }
        }
    }

    private void MutantEFX_PerformForceShoot()
    {
        if (m_MutantEFX_ShotsFired >= m_MutantEFX_ShotsTotal)
        {
            m_MutantEFX_IsForceShooting = false;
            return;
        }

        Weapon_Base weapon;
        if (GetWeaponManager() && Class.CastTo(weapon, GetHumanInventory().GetEntityInHands()))
            GetWeaponManager().Fire(weapon);

        m_MutantEFX_ShotsFired++;

        if (m_MutantEFX_ShotsFired < m_MutantEFX_ShotsTotal)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(MutantEFX_PerformForceShoot, Math.RandomIntInclusive(150, 300), false);
        else
            m_MutantEFX_IsForceShooting = false;
    }
}