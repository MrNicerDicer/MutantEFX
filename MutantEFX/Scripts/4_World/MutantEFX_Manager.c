class MutantEFX_PlayerState
{
    Man     player;
    bool    inBlurZone      = false;
    float   dropCooldown    = 0;
    float   shootCooldown   = 0;
    float   telekinesisCD   = 0;
    float   psyPushCD       = 0;
    float   suicideCD       = 0;
    bool    isLifted        = false;
    float   liftTimer       = 0;

    void MutantEFX_PlayerState(Man p)
    {
        player = p;
    }
}

class MutantEFX_EntityData
{
    private EntityAI                                m_Entity;
    private ref MutantEFX_MutantConfig              m_Config;
    private float                                   m_TickTimer = 0;
    private ref map<Man, ref MutantEFX_PlayerState> m_PlayerStates = new map<Man, ref MutantEFX_PlayerState>;

    void MutantEFX_EntityData(EntityAI entity, MutantEFX_MutantConfig config)
    {
        m_Entity = entity;
        m_Config = config;
    }

    void Cleanup()
    {
        foreach (Man cleanPlayer, MutantEFX_PlayerState cleanState : m_PlayerStates)
        {
            if (!cleanPlayer) continue;
            PlayerIdentity cleanIdent = cleanPlayer.GetIdentity();
            if (!cleanIdent) continue;
            if (cleanState.inBlurZone)
                GetGame().RPCSingleParam(cleanPlayer, MutantEFX_RPCs.RPC_PSYCHIC_BLUR_EXIT, null, true, cleanIdent);
        }
        m_PlayerStates.Clear();
    }

    void Update()
    {
        float deltaTime = 1.0;
        m_TickTimer += deltaTime;

        bool tickFired = (m_TickTimer >= m_Config.tick_interval);
        bool isAggro = MutantEFX_Manager.Get().IsEntityAggro(m_Entity);

        float searchRadius = GetMaxSearchRadius();
        array<Man> nearbyPlayers = MutantEFX_Manager.Get().GetPlayersInRadius(m_Entity, searchRadius);

        int i;
        for (i = 0; i < nearbyPlayers.Count(); i++)
        {
            Man player = nearbyPlayers.Get(i);
            if (!player || !player.IsAlive()) continue;

            PlayerIdentity ident = player.GetIdentity();
            if (!ident) continue;

            if (!m_PlayerStates.Contains(player))
                m_PlayerStates.Insert(player, new MutantEFX_PlayerState(player));

            MutantEFX_PlayerState state = m_PlayerStates.Get(player);

            state.dropCooldown  -= deltaTime;
            state.shootCooldown -= deltaTime;
            state.telekinesisCD -= deltaTime;
            state.psyPushCD     -= deltaTime;
            state.suicideCD     -= deltaTime;

            float dist = vector.Distance(m_Entity.GetPosition(), player.GetPosition());

            if (m_Config.psychic_blur_enabled == 1)
            {
                bool wantBlur = (dist <= m_Config.psychic_blur_radius && (m_Config.psychic_blur_aggro_only == 0 || isAggro));
                if (wantBlur && !state.inBlurZone)
                {
                    Param1<float> blurParam = new Param1<float>(m_Config.psychic_blur_strength);
                    GetGame().RPCSingleParam(player, MutantEFX_RPCs.RPC_PSYCHIC_BLUR_ENTER, blurParam, true, ident);
                    state.inBlurZone = true;
                }
                else if (!wantBlur && state.inBlurZone)
                {
                    GetGame().RPCSingleParam(player, MutantEFX_RPCs.RPC_PSYCHIC_BLUR_EXIT, null, true, ident);
                    state.inBlurZone = false;
                }
            }

            if (!tickFired) continue;

            if (dist <= m_Config.psychic_blur_radius)
                ApplyTickDamage(player);

            if (m_Config.drop_item_enabled == 1 && dist <= m_Config.drop_item_radius && state.dropCooldown <= 0)
            {
                if (Math.RandomFloat01() * 100.0 < m_Config.drop_item_chance)
                {
                    DayZPlayer pbDrop = DayZPlayer.Cast(player);
                    if (pbDrop)
                    {
                        EntityAI itemInHands = pbDrop.GetHumanInventory().GetEntityInHands();
                        if (itemInHands)
                        {
                            pbDrop.GetInventory().DropEntity(InventoryMode.SERVER, pbDrop, itemInHands);
                            state.dropCooldown = m_Config.drop_item_cooldown;
                        }
                    }
                }
            }

            if (m_Config.force_shoot_enabled == 1 && dist <= m_Config.force_shoot_radius && state.shootCooldown <= 0)
            {
                if (Math.RandomFloat01() * 100.0 < m_Config.force_shoot_chance)
                {
                    int shots = Math.RandomIntInclusive(1, m_Config.force_shoot_count);
                    Param1<int> shootParam = new Param1<int>(shots);
                    GetGame().RPCSingleParam(player, MutantEFX_RPCs.RPC_FORCE_SHOOT, shootParam, true, ident);
                    state.shootCooldown = m_Config.force_shoot_cooldown;
                }
            }

            if (m_Config.telekinesis_enabled == 1 && dist <= m_Config.telekinesis_radius && state.telekinesisCD <= 0 && !state.isLifted)
            {
                if (Math.RandomFloat01() * 100.0 < m_Config.telekinesis_chance)
                {
                    DayZPlayer dzLift = DayZPlayer.Cast(player);
                    if (dzLift && !dzLift.GetCommand_Vehicle())
                    {
                        float upForce = m_Config.telekinesis_lift_height * 150.0;
                        dBodyApplyImpulse(player, Vector(0, upForce, 0));

                        Param1<float> liftParam = new Param1<float>(m_Config.telekinesis_duration);
                        GetGame().RPCSingleParam(player, MutantEFX_RPCs.RPC_TELEKINESIS_LIFT_ENTER, liftParam, true, ident);

                        state.isLifted      = true;
                        state.liftTimer     = m_Config.telekinesis_duration;
                        state.telekinesisCD = m_Config.telekinesis_cooldown;
                    }
                }
            }

            if (state.isLifted)
            {
                state.liftTimer -= m_Config.tick_interval;
                if (state.liftTimer <= 0)
                {
                    GetGame().RPCSingleParam(player, MutantEFX_RPCs.RPC_TELEKINESIS_LIFT_EXIT, null, true, ident);
                    state.isLifted = false;
                }
            }

            if (m_Config.psy_push_enabled == 1 && dist <= m_Config.psy_push_radius && state.psyPushCD <= 0)
            {
                if (Math.RandomFloat01() * 100.0 < m_Config.psy_push_chance)
                {
                    DayZPlayer dzPush = DayZPlayer.Cast(player);
                    if (dzPush && !dzPush.GetCommand_Vehicle())
                    {
                        vector pushDir = player.GetPosition() - m_Entity.GetPosition();
                        pushDir[1] = 0;
                        if (pushDir.LengthSq() < 0.0001)
                            pushDir = Vector(0, 0, 1);
                        pushDir.Normalize();

                        float baseYaw = Math.Atan2(pushDir[0], pushDir[2]);
                        float yawOffset = Math.RandomFloat(-20.0, 20.0) * Math.DEG2RAD;
                        float yaw = baseYaw + yawOffset;
                        vector finalDir = Vector(Math.Sin(yaw), 0, Math.Cos(yaw));
                        finalDir.Normalize();

                        vector pushImpulse = finalDir * m_Config.psy_push_force;
                        pushImpulse[1] = m_Config.psy_push_force * 0.5;
                        dBodyApplyImpulse(player, pushImpulse);

                        GetGame().RPCSingleParam(player, MutantEFX_RPCs.RPC_PSY_PUSH, null, true, ident);
                        state.psyPushCD = m_Config.psy_push_cooldown;
                    }
                }
            }

            if (m_Config.suicide_enabled == 1 && dist <= m_Config.suicide_radius && state.suicideCD <= 0)
            {
                if (Math.RandomFloat01() * 100.0 < m_Config.suicide_chance)
                {
                    PlayerBase pbSuicide = PlayerBase.Cast(player);
                    if (pbSuicide)
                    {
                        float playerHP = pbSuicide.GetHealth("", "Health");
                        if (playerHP <= m_Config.suicide_hp_threshold && !pbSuicide.GetCommand_Vehicle())
                        {
                            state.suicideCD = m_Config.suicide_cooldown;
                            GetGame().RPCSingleParam(player, MutantEFX_RPCs.RPC_FORCE_SUICIDE, null, true, ident);
                        }
                    }
                }
            }
        }

        array<Man> toRemove = new array<Man>;
        foreach (Man trackedPlayer, MutantEFX_PlayerState trackedState : m_PlayerStates)
        {
            if (!trackedPlayer || nearbyPlayers.Find(trackedPlayer) == -1)
                toRemove.Insert(trackedPlayer);
        }

        int r;
        for (r = 0; r < toRemove.Count(); r++)
        {
            Man leaving = toRemove.Get(r);
            MutantEFX_PlayerState leavingState = m_PlayerStates.Get(leaving);
            if (leavingState && leaving)
            {
                PlayerIdentity leavingIdent = leaving.GetIdentity();
                if (leavingIdent)
                {
                    if (leavingState.inBlurZone)
                        GetGame().RPCSingleParam(leaving, MutantEFX_RPCs.RPC_PSYCHIC_BLUR_EXIT, null, true, leavingIdent);
                }
            }
            m_PlayerStates.Remove(leaving);
        }

        if (tickFired)
            m_TickTimer = 0;
    }

    private void ApplyTickDamage(Man player)
    {
        if (m_Config.damage_health > 0)
            player.AddHealth("", "Health", -m_Config.damage_health);
        if (m_Config.damage_blood > 0)
            player.AddHealth("", "Blood", -m_Config.damage_blood);
        if (m_Config.damage_shock > 0)
            player.AddHealth("", "Shock", -m_Config.damage_shock);
    }

    private float GetMaxSearchRadius()
    {
        float r = 0;
        if (m_Config.psychic_blur_enabled == 1)  r = Math.Max(r, m_Config.psychic_blur_radius);
        if (m_Config.drop_item_enabled == 1)      r = Math.Max(r, m_Config.drop_item_radius);
        if (m_Config.force_shoot_enabled == 1)    r = Math.Max(r, m_Config.force_shoot_radius);
        if (m_Config.telekinesis_enabled == 1)    r = Math.Max(r, m_Config.telekinesis_radius);
        if (m_Config.psy_push_enabled == 1)       r = Math.Max(r, m_Config.psy_push_radius);
        if (m_Config.suicide_enabled == 1)        r = Math.Max(r, m_Config.suicide_radius);
        if (m_Config.death_flash_enabled == 1)    r = Math.Max(r, m_Config.death_flash_radius);
        return Math.Max(r, 5.0);
    }
}

class MutantEFX_Manager
{
    private static ref MutantEFX_Manager instance;
    private ref map<EntityAI, ref MutantEFX_EntityData> m_TrackedEntities = new map<EntityAI, ref MutantEFX_EntityData>;

    void MutantEFX_Manager()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Update, 1000, true);
    }

    static MutantEFX_Manager Get()
    {
        if (!instance)
            instance = new MutantEFX_Manager();
        return instance;
    }

    void RegisterEntity(EntityAI entity)
    {
        if (!entity || m_TrackedEntities.Contains(entity)) return;
        if (!MutantEFX_Config.instance) return;
        MutantEFX_MutantConfig cfg = MutantEFX_Config.Get().GetConfigForEntity(entity.GetType());
        if (cfg)
            m_TrackedEntities.Insert(entity, new MutantEFX_EntityData(entity, cfg));
    }

    void OnEntityDeath(EntityAI entity)
    {
        MutantEFX_MutantConfig cfg = MutantEFX_Config.Get().GetConfigForEntity(entity.GetType());
        if (!cfg) return;
        if (cfg.death_flash_enabled != 1) return;

        vector spawnPos = entity.GetPosition();
        spawnPos[1] = spawnPos[1] + 1.0;

        ItemBase grenade = ItemBase.Cast(GetGame().CreateObject("FlashGrenade", spawnPos, false, true));
        if (grenade)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(MutantEFX_DetonateGrenade, 100, false, grenade);
    }

    private void MutantEFX_DetonateGrenade(ItemBase grenade)
    {
        if (!grenade) return;
        grenade.SetHealth("", "Health", 0);
    }

    void UnregisterEntity(EntityAI entity)
    {
        if (!m_TrackedEntities.Contains(entity)) return;
        MutantEFX_EntityData data = m_TrackedEntities.Get(entity);
        data.Cleanup();
        m_TrackedEntities.Remove(entity);
    }

    private void Update()
    {
        array<EntityAI> toRemove = new array<EntityAI>;

        foreach (EntityAI entity, MutantEFX_EntityData data : m_TrackedEntities)
        {
            if (!entity || !entity.IsAlive())
            {
                toRemove.Insert(entity);
                continue;
            }
            data.Update();
        }

        foreach (EntityAI dead : toRemove)
            UnregisterEntity(dead);
    }

    array<Man> GetPlayersInRadius(EntityAI entity, float radius)
    {
        array<Man>       result  = new array<Man>;
        array<Object>    objects = new array<Object>;
        array<CargoBase> cargos  = new array<CargoBase>;

        GetGame().GetObjectsAtPosition(entity.GetPosition(), radius, objects, cargos);

        foreach (Object obj : objects)
        {
            Man player = Man.Cast(obj);
            if (player && player.IsAlive() && player.IsPlayer())
                result.Insert(player);
        }
        return result;
    }

    bool IsEntityAggro(EntityAI entity)
    {
        return GetVelocity(entity).Length() > 1.0;
    }
}