// FUNC_NAME: RandomGenerator::getRandomFloat
float __fastcall RandomGenerator::getRandomFloat(int this)
{
    double localResult;

    if (*(int *)(this + 0xa0) != 0) // +0xA0: mUseSeededRandom flag
    {
        RandomBegin();               // Enter random context (lock/init)
        RandomGetDouble(0, &localResult); // Get double in [0,1) range
        RandomEnd();                 // Exit random context
        return (float)localResult * g_randomMultiplier; // DAT_00e2e230
    }
    return g_defaultRandomValue; // DAT_00e2eff4
}