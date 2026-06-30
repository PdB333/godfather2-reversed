// FUNC_NAME: getScaledDamage
// Address: 0x00701920
// This function is called by the damage application routine to apply a damage-type multiplier.
// It reads base damage and damage type from the object (likely a weapon or damage context),
// retrieves a pointer to global combat constants (from FUN_007079c0), and multiplies by the
// appropriate scaling factor based on the damage type (1-4). The multiplier values are stored
// at offsets 0x1df0, 0x1df8, and 0x1e00 in the global data.

float __fastcall getScaledDamage(int thisObj) {
    float baseDamage = *(float*)(thisObj + 0x354);          // +0x354: base damage value
    void* combatData = getCombatManager();                    // FUN_007079c0 - returns pointer to global combat constants singleton
    if (combatData != nullptr) {
        int damageType = *(int*)(thisObj + 0x2dc);           // +0x2dc: damage type (1,2,3,4)
        switch (damageType) {
            case 1:
                // Type 1 multiplier at global+0x1df0
                return (float)(*(float*)((int)combatData + 0x1df0) * baseDamage);
            case 2:
            case 3:
                // Types 2 and 3 share multiplier at global+0x1df8
                return (float)(*(float*)((int)combatData + 0x1df8) * baseDamage);
            case 4:
                // Type 4 multiplier at global+0x1e00
                baseDamage = *(float*)((int)combatData + 0x1e00) * baseDamage;
                break;
        }
    }
    return (float)baseDamage;
}