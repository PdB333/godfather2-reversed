// FUNC_ADDR: 0x007234c0
// Role: Returns a random float value between min and max for a given attribute index,
//       with an optional bonus from a global singleton for specific indices (1-4).
// Fields:
// - this + 0x90: float minValues[] (array of min values indexed by attribute type)
// - this + 0xbc: float maxValues[] (array of max values indexed by attribute type)
// Global references:
// - 0x012233a0 + 4: pointer to a global manager object (base address of pointer table)
// - If that manager pointer is valid (not null, not 0x1f30), a float bonus at offset 0x1fc is added

float __thiscall StatsManager::getRandomAttributeValue(float attributeIndexFloat)
{
    int attributeIndex = (int)attributeIndexFloat; // parameter is actually an integer index (e.g., 0,1,2,3,4...)

    float minValue = this->minValues[attributeIndex];   // offset 0x90 + index*4
    float maxValue = this->maxValues[attributeIndex];   // offset 0xbc + index*4

    // If min < max, pick a random value in that range
    if (minValue < maxValue)
    {
        float randomFraction = (float)_rand() * kRandScale; // kRandScale = 1.0/RAND_MAX (typically 1.0/32767)
        maxValue = randomFraction * (maxValue - minValue) + minValue;
    }

    // Special handling for attribute indices 1,2,3,4 (likely corresponding to player, enemy, etc.)
    if (attributeIndex >= 1 && attributeIndex <= 4)
    {
        // Access global pointer table at 0x012233a0, offset 4 gives a pointer to a manager
        int* globalManagerPtr = *(int**)(0x012233a0 + 4);
        if (globalManagerPtr != nullptr && globalManagerPtr != (int*)0x1f30) // 0x1f30 = sentinel for invalid
        {
            // Add bonus from the manager's field at offset 0x1fc
            maxValue += *(float*)((int)globalManagerPtr + 0x1fc);
        }
    }

    // Clamp to zero
    if (maxValue < 0.0f)
        maxValue = 0.0f;

    return maxValue;
}