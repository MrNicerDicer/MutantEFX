class MutantEFX_PPERequester_DeathFlash extends PPERequesterBase
{
    private float m_Intensity = 0.0;

    void SetIntensity(float value)
    {
        m_Intensity = Math.Clamp(value, 0.0, 1.0);
    }

    override void OnUpdate(float delta)
    {
        PPEffects.SetBlur(m_Intensity);
    }
}