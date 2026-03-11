class MutantEFX_MutantConfig
{
    ref array<string> classnames = new array<string>;
    int enabled = 1;

    int   psychic_blur_enabled      = 0;
    float psychic_blur_radius       = 25.0;
    float psychic_blur_strength     = 0.7;
    int   psychic_blur_aggro_only   = 0;

    int   drop_item_enabled         = 0;
    float drop_item_radius          = 20.0;
    float drop_item_chance          = 25.0;
    float drop_item_cooldown        = 20.0;

    int   force_shoot_enabled       = 0;
    int   force_shoot_count         = 3;
    float force_shoot_radius        = 25.0;
    float force_shoot_chance        = 20.0;
    float force_shoot_cooldown      = 25.0;

    int   telekinesis_enabled       = 0;
    float telekinesis_radius        = 15.0;
    float telekinesis_lift_height   = 3.0;
    float telekinesis_duration      = 3.0;
    float telekinesis_chance        = 15.0;
    float telekinesis_cooldown      = 30.0;

    int   psy_push_enabled          = 0;
    float psy_push_radius           = 12.0;
    float psy_push_force            = 600.0;
    float psy_push_chance           = 25.0;
    float psy_push_cooldown         = 15.0;

    int   death_flash_enabled       = 0;
    float death_flash_radius        = 20.0;
    float death_flash_intensity     = 1.0;
    float death_knock_force         = 500.0;

    int   suicide_enabled           = 0;
    float suicide_radius            = 15.0;
    float suicide_chance            = 5.0;
    float suicide_cooldown          = 60.0;
    float suicide_hp_threshold      = 60.0;

    float tick_interval             = 5.0;
    float damage_health             = 0.0;
    float damage_blood              = 0.0;
    float damage_shock              = 0.0;
    float damage_water              = 0.0;
    float damage_energy             = 0.0;

    void MutantEFX_MutantConfig()
    {
        classnames.Insert("ZmbM_HunterOld_Autumn");
    }
}

class MutantEFX_Config
{
    static ref MutantEFX_Config instance;
    ref array<ref MutantEFX_MutantConfig> mutants = new array<ref MutantEFX_MutantConfig>;

    void MutantEFX_Config()
    {
        if (!FileExist(MutantEFX_Constants.CONFIG_DIR))
            MakeDirectory(MutantEFX_Constants.CONFIG_DIR);

        string configPath = MutantEFX_Constants.CONFIG_DIR + MutantEFX_Constants.CONFIG_FILE;

        if (!FileExist(configPath))
        {
            CreateDefaultConfig();
            SaveConfig();
        }
        else
        {
            LoadConfig();
        }
    }

    static MutantEFX_Config Get()
    {
        if (!instance)
            instance = new MutantEFX_Config();
        return instance;
    }

    void CreateDefaultConfig()
    {
        mutants.Clear();

        MutantEFX_MutantConfig controller = new MutantEFX_MutantConfig();
        controller.classnames.Clear();
        controller.classnames.Insert("ZmbM_HunterOld_Autumn");
        controller.enabled                  = 1;
        controller.psychic_blur_enabled     = 1;
        controller.psychic_blur_radius      = 30.0;
        controller.psychic_blur_strength    = 0.8;
        controller.psychic_blur_aggro_only  = 0;
        controller.force_shoot_enabled      = 1;
        controller.force_shoot_radius       = 25.0;
        controller.force_shoot_count        = 5;
        controller.force_shoot_chance       = 20.0;
        controller.force_shoot_cooldown     = 25.0;
        controller.telekinesis_enabled      = 1;
        controller.telekinesis_radius       = 15.0;
        controller.telekinesis_lift_height  = 3.5;
        controller.telekinesis_duration     = 3.0;
        controller.telekinesis_chance       = 15.0;
        controller.telekinesis_cooldown     = 30.0;
        controller.psy_push_enabled         = 1;
        controller.psy_push_radius          = 20.0;
        controller.psy_push_force           = 600.0;
        controller.psy_push_chance          = 25.0;
        controller.psy_push_cooldown        = 15.0;
        controller.death_flash_enabled      = 1;
        controller.death_flash_radius       = 25.0;
        controller.death_flash_intensity    = 1.0;
        controller.death_knock_force        = 500.0;
        controller.suicide_enabled          = 1;
        controller.suicide_radius           = 15.0;
        controller.suicide_chance           = 8.0;
        controller.suicide_cooldown         = 60.0;
        controller.suicide_hp_threshold     = 100.0;
        controller.tick_interval            = 5.0;
        controller.damage_health            = 3.0;
        controller.damage_shock             = 10.0;
        mutants.Insert(controller);

        MutantEFX_MutantConfig burer = new MutantEFX_MutantConfig();
        burer.classnames.Clear();
        burer.classnames.Insert("ZmbM_PatrolNormal_Autumn");
        burer.enabled                   = 1;
        burer.psychic_blur_enabled      = 1;
        burer.psychic_blur_radius       = 25.0;
        burer.psychic_blur_strength     = 0.7;
        burer.psychic_blur_aggro_only   = 0;
        burer.drop_item_enabled         = 1;
        burer.drop_item_radius          = 20.0;
        burer.drop_item_chance          = 40.0;
        burer.drop_item_cooldown        = 15.0;
        burer.telekinesis_enabled       = 1;
        burer.telekinesis_radius        = 12.0;
        burer.telekinesis_lift_height   = 2.5;
        burer.telekinesis_duration      = 2.5;
        burer.telekinesis_chance        = 20.0;
        burer.telekinesis_cooldown      = 25.0;
        burer.death_flash_enabled       = 1;
        burer.death_flash_radius        = 15.0;
        burer.death_flash_intensity     = 0.8;
        burer.death_knock_force         = 350.0;
        burer.tick_interval             = 6.0;
        burer.damage_health             = 2.0;
        mutants.Insert(burer);
    }

    void LoadConfig()
    {
        string configPath = MutantEFX_Constants.CONFIG_DIR + MutantEFX_Constants.CONFIG_FILE;
        JsonFileLoader<MutantEFX_Config>.JsonLoadFile(configPath, this);
    }

    void SaveConfig()
    {
        string configPath = MutantEFX_Constants.CONFIG_DIR + MutantEFX_Constants.CONFIG_FILE;
        JsonFileLoader<MutantEFX_Config>.JsonSaveFile(configPath, this);
    }

    MutantEFX_MutantConfig GetConfigForEntity(string classname)
    {
        foreach (MutantEFX_MutantConfig cfg : mutants)
        {
            if (cfg.enabled == 0) continue;
            foreach (string cn : cfg.classnames)
            {
                if (cn == classname)
                    return cfg;
            }
        }
        return null;
    }
}