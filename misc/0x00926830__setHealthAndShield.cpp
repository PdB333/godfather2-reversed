// FUNC_NAME: setHealthAndShield
// Function address: 0x00926830
// Role: Clamps two float parameters to [0, s_maxValue] and stores them at offsets +0x3AC and +0x3B0 (likely health and shield of an entity).

void __thiscall setHealthAndShield(int this, float health, float shield)
{
    // Global maximum value for both fields (e.g., max health/shield)
    float maxValue = _DAT_00d5780c;

    // Clamp health to [0, maxValue]
    if (0.0f < health)
    {
        if (maxValue <= health)
        {
            health = maxValue;
        }
    }
    else
    {
        health = 0.0f;
    }
    *(float *)(this + 0x3AC) = health; // +0x3AC: health field

    // Clamp shield: if <= 0, set to 0; otherwise min with maxValue
    if (shield <= 0.0f)
    {
        *(int *)(this + 0x3B0) = 0; // store 0 as float (since undefined4 cast)
        return;
    }
    if (maxValue <= shield)
    {
        *(float *)(this + 0x3B0) = maxValue; // +0x3B0: shield field
        return;
    }
    *(float *)(this + 0x3B0) = shield;
    return;
}