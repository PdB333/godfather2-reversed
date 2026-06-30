// FUNC_NAME: SomeClass::calculateRandomScaledOffset
double __fastcall GameplayHelper::computeNoiseValue(void* thisPointer)
{
    double defaultReturn;
    float baseValue;
    float deltaScale;
    int stateIndex;

    defaultReturn = g_defaultValue1; // _DAT_00d5780c

    if (isActiveCheck()) // FUN_00800a90
    {
        stateIndex = getStateIndex(); // FUN_00701050
        if (*(int*)((char*)thisPointer + 0x24) != 0) // pointer to struct with offsets
        {
            // struct at offset 0x24 from this:
            // +0x68: float multiplier
            // +0xb0: float array indexed by stateIndex
            float* dataArray = (float*)(*(int*)((char*)thisPointer + 0x24) + 0xb0);
            baseValue = dataArray[stateIndex];
            float multiplier = *(float*)(*(int*)((char*)thisPointer + 0x24) + 0x68);
            deltaScale = multiplier * baseValue;

            int randomInt = rand();
            // g_invRandMax = DAT_00e44590, g_factor = DAT_00d5eee4
            double result = (double)randomInt * g_randScaleFactor * deltaScale * g_globalFactor + baseValue - deltaScale;
            return result;
        }
        defaultReturn = g_secondaryDefault; // _DAT_00d5c458
    }
    return defaultReturn;
}