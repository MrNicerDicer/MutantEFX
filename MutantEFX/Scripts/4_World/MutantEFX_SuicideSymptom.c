class MutantEFX_SuicideSymptom extends SymptomBase
{
    static const int SYMPTOM_ID = 7700;

    override void OnInit()
    {
        m_SymptomType = SymptomTypes.PRIMARY;
        m_Priority = 100;
        m_ID = SYMPTOM_ID;
        m_DestroyOnAnimFinish = true;
        m_SyncToClient = false;
        m_Duration = 5;
        super.OnInit();
    }

    override bool CanActivate()
    {
        return true;
    }

    override void OnGetActivatedServer(PlayerBase player)
    {
        ItemBase weapon = m_Player.GetItemInHands();
        int CMD_ID = DayZPlayerConstants.CMD_SUICIDEFB_UNARMED;
        int stancemask = DayZPlayerConstants.STANCEMASK_CROUCH;
        string suicideStr;

        if (weapon)
        {
            if (weapon.ConfigIsExisting("suicideAnim"))
                suicideStr = weapon.ConfigGetString("suicideAnim");

            if (weapon.IsKindOf("Pistol_Base"))
            {
                CMD_ID = DayZPlayerConstants.CMD_SUICIDEFB_PISTOL;
                stancemask = DayZPlayerConstants.STANCEMASK_CROUCH;
            }
            else if (Weapon_Base.Cast(weapon))
            {
                CMD_ID = DayZPlayerConstants.CMD_SUICIDEFB_RIFLE;
                stancemask = DayZPlayerConstants.STANCEMASK_CROUCH;
            }
            else if (suicideStr == "onehanded")
            {
                CMD_ID = DayZPlayerConstants.CMD_SUICIDEFB_1HD;
                stancemask = DayZPlayerConstants.STANCEMASK_CROUCH;
            }
            else if (suicideStr == "fireaxe")
            {
                CMD_ID = DayZPlayerConstants.CMD_SUICIDEFB_FIREAXE;
                stancemask = DayZPlayerConstants.STANCEMASK_ERECT;
            }
            else if (suicideStr == "pitchfork")
            {
                CMD_ID = DayZPlayerConstants.CMD_SUICIDEFB_PITCHFORK;
                stancemask = DayZPlayerConstants.STANCEMASK_ERECT;
            }
            else if (suicideStr == "sword")
            {
                CMD_ID = DayZPlayerConstants.CMD_SUICIDEFB_SWORD;
                stancemask = DayZPlayerConstants.STANCEMASK_ERECT;
            }
            else if (suicideStr == "spear")
            {
                CMD_ID = DayZPlayerConstants.CMD_SUICIDEFB_SPEAR;
                stancemask = DayZPlayerConstants.STANCEMASK_ERECT;
            }
            else if (suicideStr == "woodaxe")
            {
                CMD_ID = DayZPlayerConstants.CMD_SUICIDEFB_WOODAXE;
                stancemask = DayZPlayerConstants.STANCEMASK_ERECT;
            }
        }

        PlayAnimationFB(CMD_ID, stancemask, GetDuration());
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(MutantEFX_TriggerDeath, 6000, false, player);
    }

    private void MutantEFX_TriggerDeath(PlayerBase player)
    {
        if (!player || !player.IsAlive()) return;
        PlayerIdentity ident = player.GetIdentity();
        if (ident)
            GetGame().RPCSingleParam(player, MutantEFX_RPCs.RPC_PLAY_GUNSHOT, null, true, ident);
        player.SetHealth("", "Health", 0);
        player.SetHealth("", "Blood", 0);
        player.SetHealth("", "Shock", 0);
        player.MutantEFX_ResetSuicide();
    }

    override void OnGetDeactivatedServer(PlayerBase player)
    {
        if (player && player.IsAlive())
            player.SetHealth("", "Shock", 0);
        player.MutantEFX_ResetSuicide();
    }

    override void OnUpdateServer(PlayerBase player, float deltatime)
    {
    }

    override SmptAnimMetaBase SpawnAnimMetaObject()
    {
        return new SmptAnimMetaFB();
    }
}