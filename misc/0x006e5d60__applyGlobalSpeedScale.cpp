// FUNC_NAME: applyGlobalSpeedScale
void applyGlobalSpeedScale(float speedMultiplier)
{
    // Global speed scaling factors (e.g., difficulty adjustment, global time scale)
    // DAT_00e445c8 and _DAT_00d5c458 are likely engine-wide multipliers.
    double scaled = (double)(speedMultiplier * g_globalSpeedFactorA * g_globalSpeedFactorB);

    // Call an internal update/notification function (FUN_00b99e20)
    onSpeedScaleUpdated();

    // Store the result as the object's current speed at offset +0x54 (e.g., m_speed)
    this->m_speed = (float)scaled;
}