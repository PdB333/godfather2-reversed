// FUNC_NAME: applyConfigurationParameters
void __thiscall applyConfigurationParameters(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5, uint32_t param6)
{
    // First, set the global flag indicating configuration is being applied
    g_configActiveFlag = 1;  // _DAT_011f3d10

    // Clamp first pair of globals (g_limitA and g_limitB) to ensure they are at least 0xCE and at most 0xCE
    if (g_limitA < 0xCE) {
        g_limitA = 0xCE;
    }
    if (g_limitB > 0xCD) {
        g_limitB = 0xCE;
    }

    // Apply parameter 1 to global config slot 1
    g_configSlot1 = param1;  // _DAT_011f3c84

    // Clamp second pair of globals (g_limitC and g_limitD) to ensure they are at least 0x13 and at most 0x13
    if (g_limitC < 0x13) {
        g_limitC = 0x13;
    }
    if (g_limitD > 0x12) {
        g_limitD = 0x13;
    }

    // Apply parameter 2 to global config slot 2
    g_configSlot2 = param2;  // _DAT_011f3a24

    // Clamp second pair again to 0x14
    if (g_limitC < 0x14) {
        g_limitC = 0x14;
    }
    if (g_limitD > 0x13) {
        g_limitD = 0x14;
    }

    // Apply parameter 3 to global config slot 3
    g_configSlot3 = param3;  // _DAT_011f3a28

    // Clamp first pair to 0xD1
    if (g_limitA < 0xD1) {
        g_limitA = 0xD1;
    }
    if (g_limitB > 0xD0) {
        g_limitB = 0xD1;
    }

    // Apply parameter 4 to global config slot 4
    g_configSlot4 = param4;  // _DAT_011f3d1c

    // Clamp first pair to 0xCF
    if (g_limitA < 0xCF) {
        g_limitA = 0xCF;
    }
    if (g_limitB > 0xCE) {
        g_limitB = 0xCF;
    }

    // Apply parameter 5 to global config slot 5
    g_configSlot5 = param5;  // _DAT_011f3d14

    // Clamp first pair to 0xD0
    if (g_limitA < 0xD0) {
        g_limitA = 0xD0;
    }

    // Apply parameter 6 to global config slot 6
    g_configSlot6 = param6;  // _DAT_011f3d18

    // Final clamp on second pair to 0xD0
    if (g_limitD > 0xCF) {
        g_limitD = 0xD0;
    }
}