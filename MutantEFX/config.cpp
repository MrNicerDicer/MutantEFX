class CfgPatches
{
    class MutantEFX
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data","DZ_Scripts"};
    };
};

class CfgMods
{
    class MutantEFX
    {
        dir = "MutantEFX";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "MutantEFX";
        credits = "";
        author = "MrNicerDicer";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";

        dependencies[] = {"Game","World","Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"MutantEFX/Scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"MutantEFX/Scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"MutantEFX/Scripts/5_Mission"};
            };
        };
    };
};