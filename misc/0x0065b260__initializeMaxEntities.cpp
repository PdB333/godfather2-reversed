// FUNC_NAME: initializeMaxEntities
// Function address: 0x0065b260
// Role: Initialize global maximum entity count to 256 (0x100). Calls another initialization function first.

void initializeMaxEntities()
{
    initializeSomeOtherSystem();  // Calls FUN_0065b320 - likely sets up related state

    // Clamp global max count to exactly 256
    if (g_maxEntityCount != 0x100) {
        g_maxEntityCount = 0x100;
    }
}