// FUNC_NAME: setTimeScale
// Sets global timing parameters based on a time scale input.
// This updates various cached values used for physics, animation, or camera smoothing.
void setTimeScale(float timeScale)
{
    // Base time step constant (likely derived from frame rate target)
    float baseTimeStep = DAT_00e2b1a4;

    // Store the raw time scale input
    g_timeScaleInput = timeScale;                        // DAT_0110ae4c
    g_timeScaleDuplicate = timeScale;                     // DAT_01217ab4

    // Compute inverted time scale (used for scaling multipliers)
    float invTimeScale = baseTimeStep / timeScale;

    g_invTimeScale = invTimeScale;                        // DAT_01217ab0
    g_invTimeScaleDuplicate = invTimeScale;               // DAT_01217ab8

    // Scaled values combining multipliers
    g_scaledMultiplier1 = invTimeScale * DAT_00e2e230;    // DAT_01206a30
    g_scaledMultiplier2 = invTimeScale * DAT_00e44638;    // _DAT_01217abc

    // A more complex scaling: base / (timeScale * another factor)
    g_complexScale = baseTimeStep / (timeScale * DAT_00e2b04c); // _DAT_01217ac0
}