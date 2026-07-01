//FUNC_NAME: RandomManager::updateSeed
void RandomManager::updateSeed(void)
{
    float fVar1;
    uint uVar2;
    ulonglong seedValue;
    undefined1 someFlag;
    int outFrameCount;
    int outDeltaTime;
    undefined4 unused;

    outFrameCount = 0;
    outDeltaTime = 0;
    unused = 0;
    getTimeInfo(&outFrameCount); // FUN_008c73a0 - retrieves frame count and delta time
    uVar2 = g_randomSeed; // DAT_0112fef4
    if (outDeltaTime != 0) {
        uVar2 = g_randomMask & g_randomCounter; // DAT_010c2678 & DAT_012054b4
        g_randomCounter = g_randomCounter + 1; // DAT_012054b4
        fVar1 = (float)outDeltaTime;
        if (outDeltaTime < 0) {
            fVar1 = fVar1 + g_floatAdjust; // DAT_00e44578 (likely 0.5 for rounding)
        }
        seedValue = (ulonglong)ROUND(fVar1 * *(float *)(&g_randomMultipliers + uVar2 * 4)); // DAT_010c2680
        advanceRandom(); // FUN_008fe990 - advances random state
        uVar2 = g_randomResult; // DAT_0112ff00
    }
    seedValue = (ulonglong)uVar2;
    someFlag = 0;
    applyRandomValue(&seedValue, 0); // FUN_00408a00 - applies seed to some system
    if (outFrameCount != 0) {
        releaseResource(outFrameCount); // FUN_009c8f10 - frees allocated resource
    }
    return;
}