// FUN_0048bf40: WeightedQueryManager::computeWeightedValue

float __thiscall WeightedQueryManager::computeWeightedValue(void* this, int targetId, float baseValue)
{
    uint index;
    float result;
    // Local structure passed to internal function (likely a ray/intersection data)
    struct TempData {
        int   objectPtr;          // low 32-bit of pointer
        int   someHigh;           // high 32 from field at this+0x1c
        double data1;             // from this+0x24 (8 bytes)
        double data2;             // from this+0x2c
        double data3;             // from this+0x34
        double data4;             // from this+0x3c
    } tempData;

    result = 0.0f;
    if (*(uint*)((uintptr_t)this + 0x14) != 0) // +0x14: m_objectCount
    {
        // Search for object with matching ID (stored at object+0x00)
        for (index = 0; index < *(uint*)((uintptr_t)this + 0x14); index++)
        {
            if (**(int**)(*(int*)((uintptr_t)this + 0x10) + index * 4) == targetId)
                break;
        }
        if (index >= *(uint*)((uintptr_t)this + 0x14))
            return 0.0f; // Not found

        // Copy data from this into temporary structure
        // +0x1c is a 64-bit field (likely a double or two ints)
        // The high 32 bits of that field become part of tempData along with the found object's pointer
        tempData.objectPtr = *(int*)(*(int*)((uintptr_t)this + 0x10) + index * 4); // pointer to found object
        tempData.someHigh = (int)((unsigned long long)*(uint64_t*)((uintptr_t)this + 0x1c) >> 32);
        tempData.data1 = *(double*)((uintptr_t)this + 0x24);
        tempData.data2 = *(double*)((uintptr_t)this + 0x2c);
        tempData.data3 = *(double*)((uintptr_t)this + 0x34);
        tempData.data4 = *(double*)((uintptr_t)this + 0x3c);

        // If the found object pointer is valid, adjust baseValue
        if (tempData.objectPtr != 0)
        {
            // +0x18 in the object is a weight factor
            baseValue = baseValue / (float)*(int*)(tempData.objectPtr + 0x18);
            result = baseValue;
            // Call function that processes the structure (likely computes distance or effect)
            FUN_00488210(&tempData);
            // Square the result
            result = result * baseValue;
        }
    }
    return result;
}