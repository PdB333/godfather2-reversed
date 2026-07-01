// FUNC_NAME: OverlapManager::processOverlapEvent
void __thiscall OverlapManager::processOverlapEvent(int thisPtr, int overlapType, OverlapData* overlapData, int otherObject, bool hasExtraData)
{
    uint hashId;
    float currentValue;
    float storedValue;
    uint flags;
    int lookupResult;
    uint extraData;
    float result;
    uint bitFlags;
    int vtableBase;
    int methodPtr;

    extraData = 0;
    if (hasExtraData) {
        extraData = *(int*)((int)overlapData + 0xc); // +0xc: optional extra data
    }

    // Compute overlap condition via FUN_00893e70
    // This likely checks if the objects overlap or are within certain bounds
    currentValue = 0.0f;
    storedValue = *(float*)((int)overlapData + 8); // +0x8: stored threshold value

    if (!FUN_00893e70(&currentValue, *(int*)((int)overlapData + 4), otherObject, 1, 1, 0)) {
        return; // Overlap check failed
    }

    // Compare result based on overlapType
    if (overlapType == 8) { // "going out" or "less than" threshold?
        if (storedValue <= currentValue) {
            return; // Not yet triggered
        }
    } else if (overlapType == 9) { // "entering" or "greater than" threshold
        if (currentValue <= storedValue) {
            return; // Already inside
        }
    } else {
        return; // Invalid overlap type
    }

    // Build flags from overlapData + 3 (low 2 bits) and otherObject's flags
    flags = *(byte*)((int)overlapData + 3) & 3; // +0x3: two bits for type
    bitFlags = *(byte*)(otherObject + 0x10) & 5; // +0x10: bits 0 and 2 from other object's flags
    if (bitFlags != 0) {
        flags |= 0x80000000;
    }

    hashId = *(uint*)((int)overlapData + 4); // +0x4: hash identifier

    // Check against known hash IDs (likely for specific trigger types)
    if (hashId < 0x61d5bbab) {
        if (hashId == 0x61d5bbaa) return;
        if (hashId == 0x1722f6a0) return;
        if (hashId == 0x471e201b) return;
        if (hashId == 0x4ea8b900) return;
    } else {
        if (hashId == 0xe7ad7581) return;
        if (hashId == 0xe83af06c) {
            // Special handling: invoke method on a component referenced by thisPtr+0x38
            // The component's vtable at offset 0x1dc is called with rounded storedValue
            int componentPtr = *(int*)(thisPtr + 0x38); // +0x38: pointer to a component (e.g., trigger handler)
            if (componentPtr == 0) return;
            if (componentPtr == 0x48) return; // Sentinel value?
            // Adjust to get base of component class (subtract 0x48)
            int* componentBase = (int*)(componentPtr - 0x48);
            if (componentBase == 0) componentBase = (int*)0; // redudant check
            float roundedValue = (float)(int)(storedValue + 0.5f); // approximation of ROUND
            (**(code**)(*componentBase + 0x1dc))(roundedValue); // virtual call
            return;
        }
    }

    // Default handling: if other object has interaction flags (bit 0 or bit 2 set)
    if (((*(byte*)(otherObject + 0x10) & 1) != 0) || (bitFlags != 0)) {
        lookupResult = FUN_00893470(hashId); // Lookup based on hash
        if (lookupResult != 0) {
            FUN_00894d00(lookupResult, storedValue, flags, extraData);
        }
    }
}