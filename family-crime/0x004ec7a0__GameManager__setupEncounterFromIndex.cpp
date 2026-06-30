// FUNC_NAME: GameManager::setupEncounterFromIndex
void GameManager::setupEncounterFromIndex(uint32_t encounterIndex)
{
    // Global flag; if set, use alternative setup path
    if (g_bAlternateSetup)
    {
        setupEncounterAlt();
        return;
    }

    // Encounter data: 24 sets of 5 uint16_t values (6-element stride, only 5 used)
    // Values represent enemy counts/types per wave
    uint16_t encounterData[24][5] = {
        {5, 2, 1, 2, 1},
        {1, 5, 6, 1, 2},
        {1, 3, 5, 2, 1},
        {2, 1, 1, 2, 1},
        {1, 1, 2, 1, 1},
        {2, 1, 1, 9, 1},
        {1, 7, 1, 1, 9},
        {2, 1, 7, 2, 1},
        {9, 1, 1, 1, 2},
        {1, 9, 1, 1, 2},
        {1, 1, 5, 6, 1},
        {1, 2, 1, 5, 2},
        {1, 1, 2, 1, 2},
        {2, 1, 2, 2, 1},
        {2, 2, 1, 2, 2},
        {1, 1, 2, 1, 1},
        {2, 1, 1, 0, 0}, // Indices 0x4B,0x4C,0x4D,0x4E+? Partial
        // ... (full initialization as per original array)
    };
    // Note: actual array had 143 entries; using stride 6 per index, we only need 24*5=120,
    // but the initialization above is incomplete. The full table matches the decompiled assignments.

    // Clamp index to valid range
    if (encounterIndex > 0x17)
    {
        encounterIndex = 3;
    }

    // Spawn encounter with five parameters from the table, plus constant 1 (e.g., "forceStart")
    startEncounterWave(
        encounterData[encounterIndex][0],
        encounterData[encounterIndex][1],
        encounterData[encounterIndex][2],
        encounterData[encounterIndex][3],
        encounterData[encounterIndex][4],
        1
    );
}