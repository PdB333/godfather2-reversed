// FUNC_NAME: CrimeManager::generateGangsterCount

// Function address: 0x00776570
// Identified role: Generates a random count of gangsters for a crime scene,
// based on a maximum value stored at +0x32c and global difficulty parameters.

// Forward declarations of helper functions
extern bool isGameActive();
extern void setGangsterCount(int count);

// Global constants (from game data)
extern float g_minCountMultiplier;    // _DAT_00d5c458 - scales the minimum count
extern float g_randomFactor;          // DAT_00e44590 - scaling factor for random component
extern float g_floatCorrection;       // DAT_00e44578 - correction for negative float conversion

// Note: The original function uses __thiscall, param_1 is the 'this' pointer.
void CrimeManager::generateGangsterCount()
{
    float fVar1;
    float fVar6;
    int randomInt;
    uint result;

    if (!isGameActive())
    {
        setGangsterCount(1);
        return;
    }

    uint maxCount = *(uint *)(this + 0x32c); // Maximum possible gangster count
    if (maxCount > 30)
    {
        maxCount = 30;
    }

    fVar1 = (float)(int)maxCount;
    if ((int)maxCount < 0)
    {
        fVar1 = fVar1 + g_floatCorrection; // Handle negative float conversion
    }

    fVar6 = fVar1 * g_minCountMultiplier; // Adjusted lower bound

    randomInt = rand();
    // Compute a random offset within [0, (max - adjusted) )
    int randomOffset = (int)(long long)((float)randomInt * g_randomFactor * (fVar1 - fVar6));
    result = (uint)((int)fVar6 + randomOffset);
    if (randomOffset < 0 && result > maxCount) 
    { /* no explicit check, but the clamp below handles it */ }

    result = min(result, maxCount); // Clamp to max

    // Ensure result is at least 2, but not more than maxCount if maxCount is small
    if (result < 2)
    {
        result = 2;
    }
    if (maxCount < 3)
    {
        result = maxCount;
    }

    setGangsterCount(result);
}