// FUNC_NAME: SpawnManager::canSpawnType
bool SpawnManager::canSpawnType(int typeId) {
    // Only check for entity types 1 and 3 (e.g., gangsters, vehicles?)
    if (typeId != 3 && typeId != 1) {
        return true; // No limit for other types
    }

    // Get a random threshold from global random source (likely engine RNG)
    long double randomFloat = FUN_00b9cce0(*(double*)0x00d8df50); // global seed
    unsigned int threshold = (unsigned int)(randomFloat + 0.5); // round to nearest int

    // Count current entities of this type in the spawn list
    unsigned int currentCount = 0;
    int numSlots = *(int*)((uint)this + 0x50); // +0x50: number of spawn slots
    if (numSlots > 0) {
        int** slotArray = *(int***)((uint)this + 0x4c); // +0x4c: array of pointers to slot objects
        for (int i = 0; i < numSlots; i++) {
            // Each slot has type ID at offset +0x10
            if (*(int*)(slotArray[i] + 0x10) == typeId) {
                currentCount++;
            }
        }
    }

    // Allow spawn only if current count is below threshold
    return currentCount < threshold;
}