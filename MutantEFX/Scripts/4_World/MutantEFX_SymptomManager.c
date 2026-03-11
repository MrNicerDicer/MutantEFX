modded class SymptomManager
{
    override void Init()
    {
        super.Init();
        RegisterSymptom(new MutantEFX_SuicideSymptom);
    }
}