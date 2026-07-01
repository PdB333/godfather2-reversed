// Xbox PDB: EARS_Apt_UIHud_UpdatePlayerHealth
// FUNC_NAME: Sentient::updateHealth

void __thiscall Sentient::updateHealth(float damage, float resistance, float secondaryDamage)
{
    // Check if entity is alive/damageable (offset +0x48)
    if (!m_active) {  // +0x48: bool active flag
        return;
    }

    float primaryCalc = (g_damageMultiplierBase / resistance) * damage * g_maxHealth;
    // Clamp primary delta to [0, g_maxHealth]
    if (primaryCalc > 0.0f) {
        if (primaryCalc > g_maxHealth) {
            primaryCalc = g_maxHealth;
        }
    } else {
        primaryCalc = 0.0f;
    }

    float secondaryCalc = (g_damageMultiplierBase / resistance) * secondaryDamage * g_maxHealth;
    if (secondaryCalc > 0.0f) {
        if (secondaryCalc > g_maxHealth) {
            secondaryCalc = g_maxHealth;
        }
    } else {
        secondaryCalc = 0.0f;
    }

    // Only update if values changed (offset +0x64 and +0x68)
    if (primaryCalc != m_primaryHealth || secondaryCalc != m_secondaryHealth) {
        m_primaryHealth = primaryCalc;
        m_secondaryHealth = secondaryCalc;

        // Notify game system of health change
        FUN_005a04a0("UpdateHealth", 0, &DAT_00d8a64c, 0);
    }
}