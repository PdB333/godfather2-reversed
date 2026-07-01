// FUNC_NAME: BaseVehicle::getHealthRatioBasedModifier

float __fastcall BaseVehicle::getHealthRatioBasedModifier(void* this) {
    // this: pointer to BaseVehicle instance
    // Reads a pointer to a damage/stats subobject at offset +0x19c
    int* damageData = *(int**)((char*)this + 0x19c);
    // damageData points to a struct with:
    // +0x68: current health (as signed int, then converted to float)
    // +0x64: max health (as signed int, then converted to float)
    // Global constants:
    // DAT_00e44578: 4294967296.0f (used to correct negative signed int conversion to unsigned float)
    // _DAT_00d7bcb0: threshold ratio (e.g., 0.5f)
    // DAT_0112f938: pointer to a config/manager object; +0xc4 is a float value returned when condition met

    float currentHealth = (float)damageData[0x68 / 4];
    if (damageData[0x68 / 4] < 0) {
        currentHealth += DAT_00e44578;
    }
    float maxHealth = (float)damageData[100 / 4]; // offset 0x64
    if (damageData[100 / 4] < 0) {
        maxHealth += DAT_00e44578;
    }

    float ratio = currentHealth / maxHealth;
    float result = 0.0f;
    if (ratio < _DAT_00d7bcb0) {
        // Below threshold, return a configurable modifier
        result = *(float*)(DAT_0112f938 + 0xc4);
    }
    return result;
}