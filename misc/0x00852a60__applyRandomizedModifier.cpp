// FUNC_NAME: applyRandomizedModifier
void applyRandomizedModifier(void* entity1, void* entity2, int* modifierTable1, int* modifierTable2, int baseValue)
{
    // Global random seed counter and float table for randomization
    extern uint g_randomIndexMask; // DAT_010c2678 (mask)
    extern uint g_randomCounter;   // DAT_012054b4 (incremented each call)
    extern float g_randomTable[];  // DAT_010c2680 (float array)

    // Update random seed (likely srand or similar)
    randomizeSeed(); // FUN_005e3070

    // Compute index into random table using counter and mask
    uint index = g_randomCounter & g_randomIndexMask;
    g_randomCounter++;

    // Apply random multiplier to base value, round to int
    int variedValue = (int)(round((float)baseValue * g_randomTable[index]));

    int localValue = variedValue; // copy for modification

    // Apply first modifier to entity1
    int modifierHandle = getModifierFromTable(*modifierTable1, &localValue); // FUN_005e6550
    if (modifierHandle != 0) {
        applyModifier(modifierHandle, entity1); // FUN_005e6580
    }

    // Apply second modifier to entity2
    modifierHandle = getModifierFromTable(*modifierTable2, &localValue);
    if (modifierHandle != 0) {
        applyModifier(modifierHandle, entity2);
    }
}