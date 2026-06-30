// FUNC_NAME: AnimationCache::findOrCreatePose
float* __thiscall AnimationCache::findOrCreatePose(int this,
                                                   float timeOrWeight,
                                                   float* inputVector,
                                                   float angle)
{
    // Count of cached entries at offset +0x234
    uint cacheCount = *(uint*)(this + 0x234);
    uint idx = 0;

    // Search existing entries
    if (cacheCount != 0) {
        // Array of pointers to cache entries starts at +0x20c
        uint* entryPtrArray = (uint*)(this + 0x20c);
        do {
            float* entry = (float*)*entryPtrArray;
            // Check if the 5th float (float[4]) equals 'angle' and 4th float (float[3]) equals 'timeOrWeight'
            if (entry[4] == angle && entry[3] == timeOrWeight) {
                // Fast approximate equality for the first 3 floats (vector components)
                // Uses bitwise AND to strip sign bits and compare as float with epsilon
                float diff0 = (float)((uint)(entry[0] - inputVector[0]) & 0x7FFFFFFF);
                float diff1 = (float)((uint)(entry[1] - inputVector[1]) & 0x7FFFFFFF);
                float diff2 = (float)((uint)(entry[2] - inputVector[2]) & 0x7FFFFFFF);
                if (diff0 <= 0.01f && diff1 <= 0.01f && diff2 <= 0.01f) { // epsilon
                    return entry;
                }
            }
            idx++;
            entryPtrArray++;
        } while (idx < cacheCount);
    }

    // If not found and cache not full (max 10 entries)
    if (cacheCount < 10) {
        // Allocate new entry (0x30 bytes = 12 floats) via allocator vtable at +0x1e4
        void* allocFunc = *(void**)(this + 0x1e4);
        // Allocator call: (*(code**)(*allocFunc))(0x30, &localStack);
        float* newEntry = (float*)((int (__thiscall*)(void*, int, void*))allocFunc)(0x30, &localStack);
        if (newEntry == nullptr) {
            return nullptr;
        }

        // Zero initialization (filling 8 floats from index 3 to 10, then index 0 to 2)
        newEntry[3] = 0.0f;
        newEntry[4] = 0.0f;
        newEntry[5] = 0.0f;
        newEntry[6] = 0.0f;
        newEntry[7] = 0.0f;
        newEntry[8] = 0.0f;
        newEntry[9] = 0.0f;
        newEntry[10] = 0.0f;
        newEntry[11] = 0.0f;
        newEntry[2] = 0.0f;
        newEntry[1] = 0.0f;
        newEntry[0] = 0.0f;

        // Set the 5th float to the passed angle
        newEntry[4] = timeOrWeight;
        // 4th float set to 0.0 (local stack variable)
        newEntry[3] = 0.0f;
        // The 6th float is assigned the reinterpreted pointer value (likely a bug or placeholder)
        newEntry[5] = (float)(int)inputVector;  // suspicious cast

        // Copy the first 8 bytes (two floats) from inputVector into entry's first two floats
        *(double*)newEntry = *(double*)inputVector;
        // Set third float
        newEntry[2] = inputVector[2];

        // Add to cache if still room
        if (*(uint*)(this + 0x234) < 10) {
            *(float**)(this + 0x20c + *(uint*)(this + 0x234) * 4) = newEntry;
            *(int*)(this + 0x234) = *(int*)(this + 0x234) + 1;
            return newEntry;
        }
    }

    return nullptr;
}