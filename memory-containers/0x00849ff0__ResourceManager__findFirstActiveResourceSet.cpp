// FUNC_NAME: ResourceManager::findFirstActiveResourceSet
undefined4 __fastcall ResourceManager::findFirstActiveResourceSet(int this)
{
    int entityPtr;
    int resolvedObj;
    uint *bucketPtr;
    int* resourceArrayPtr;
    int diff;
    uint idx;
    uint bucketIndex;
    uint count;

    // Get entity count
    count = *(uint*)(this + 0x14);
    if (count == 0) {
        return 0;
    }

    // Scan through entity list to find first active one
    idx = 0;
    while (true) {
        entityPtr = *(int*)(*(int*)(this + 0x10) + idx * 4);  // entity from array at +0x10
        // Resolve handle at entity+0x84 to actual object
        resolvedObj = HandleToPointer(entityPtr + 0x84);  // FUN_008495c0
        if (resolvedObj != 0 && *(char*)(resolvedObj + 0xad) != '\0') {
            break;
        }
        idx++;
        if (count <= idx) {
            return 0;
        }
    }

    // Compute number of resource slots (each 0x50 bytes)
    diff = *(int*)(resolvedObj + 0x80) - *(int*)(resolvedObj + 0x7c);
    int cachedResult = *(undefined4*)(entityPtr + 0x50);  // potential return value

    // If no slots, just return the cached value
    if (diff / 0x50 == 0) {
        return cachedResult;
    }

    // Verify that all resource entries in the array at +0x8c have type 3
    resourceArrayPtr = *(int**)(resolvedObj + 0x8c);
    idx = 0;
    while (true) {
        // Hash table lookup for the resource ID (stored at +4 in each array element)
        bucketIndex = *(uint*)(*resourceArrayPtr + 4) % *(uint*)(DAT_0122337c + 0x54);
        bucketPtr = *(uint**)(*(int*)(DAT_0122337c + 0x50) + bucketIndex * 4);
        while (bucketPtr != (uint*)0x0) {
            if (*bucketPtr == *(uint*)(*resourceArrayPtr + 4)) {
                break;
            }
            bucketPtr = (uint*)bucketPtr[2];  // next bucket
        }
        if (bucketPtr == (uint*)0x0) {
            return 0;
        }
        // Check that the found resource's type is 3
        if (bucketPtr[1] == 0) {
            return 0;
        }
        if (*(int*)(bucketPtr[1] + 0x24) != 3) {
            return 0;
        }
        idx++;
        resourceArrayPtr++;
        if ((uint)((*(int*)(resolvedObj + 0x80) - *(int*)(resolvedObj + 0x7c)) / 0x50) <= idx) {
            return cachedResult;
        }
    }
}