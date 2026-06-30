// FUNC_NAME: CharacterManager::loadCharacterFromSlot
// Address: 0x00671510
// Builds a character from a slot table entry, creates animation and render objects.

int CharacterManager::loadCharacterFromSlot(int slotIndex, int *outError) {
    int errorCode = 0;
    uint minTime = 0xffff;
    uint maxTime = 0;
    // The slot stride is 0x3C (60 bytes), max 128 slots (0x7F mask)
    int slotBase = this + ((slotIndex & 0x7f) * 0x3c);
    if (*(ushort*)(slotBase + 0x1e) != slotIndex) {
        // Slot ID mismatch
        errorCode = 0x4e23;
        *outError = errorCode;
        return 0;
    }
    // Check if slot is already loaded via internal error check
    checkError(&errorCode); // FUN_00672320(this, &errorCode)
    if (errorCode != 0) {
        *outError = errorCode;
        return 0;
    }
    *outError = 0;

    // Pointer to optional attachment/skeleton parent (slot+0x30)
    int* parentData = *(int**)(slotBase + 0x30);
    if (parentData == 0) {
        parentData = 0;
    }

    // Read count of items from slot (slot+0x1c)
    int count = *(ushort*)(slotBase + 0x1c); // number of bones/parts?
    int offsetInTable = count * 8; // each entry 8 bytes?
    ushort numItems = *(ushort*)(* (int**) (this + 0x14) + offsetInTable); // from model data table
    int loopIndex = (short)numItems - 1;
    int tableStride = (short)numItems * 4;

    // Allocate three arrays for objects (slot+0x4c, +0x50, +0x54)
    *(int**)(slotBase + 0x4c) = allocateArray(); // FUN_00673070
    *(int**)(slotBase + 0x50) = allocateArray();
    *(int**)(slotBase + 0x54) = allocateArray();
    *(short*)(slotBase + 0x48) = 0; // child counter

    // Loop over items in reverse (descending)
    while (loopIndex >= 0 && errorCode == 0) {
        // Read an index from a level-of-detail or bone index table
        int lodDataBase = *(int**)(this + 0x14); // base pointer for model data
        int* lodTable = *(int**)(lodDataBase + 4 + offsetInTable); // pointer to array of ushort
        ushort lodEntry = *(ushort*)(lodTable + loopIndex * 2);
        int geometryOffset = lodEntry * 0xc4; // stride for geometry data

        int* geometryTable = *(int**)(this + 0x0c); // geometry data table base
        ushort materialIndex = *(ushort*)(geometryTable + geometryOffset + 2);
        ushort skeletonRef = *(ushort*)(geometryTable + geometryOffset);
        int skeletonOffset = skeletonRef * 0xc; // stride for skeleton entries

        int* skeletonBase = *(int**)(this + 0x04);
        int* skeletonEntry = skeletonBase + skeletonOffset;
        int* boneData = *(int**)(skeletonEntry + 4);
        int renderFlags = *(int*)(skeletonEntry + 8);

        // Copy some internal bone data pointer
        *(int*)(boneData + 4) = *(int*)(boneData + 0xc);

        uint transformIndex = *(ushort*)(skeletonBase + skeletonOffset); // another index

        // Store the transform pointer in the third array (slot+0x54)
        *(int*)(*(int*)(slotBase + 0x54) + loopIndex * 4) = *(int*)(boneData + 0x14);

        // Create the render/animation object (returns pointer to new object)
        int* newObject = createObject(transformIndex, materialIndex, boneData, renderFlags, parentData, &errorCode); // FUN_00675810
        *(int*)(*(int*)(slotBase + 0x50) + loopIndex * 4) = newObject;

        if (errorCode == 0) {
            int* obj = newObject;
            // Track min/max time values from object's animation (slot+0x6c, +0x6e)
            if (*(ushort*)(obj + 0x6c) < minTime) {
                minTime = *(ushort*)(obj + 0x6c);
            }
            if (*(ushort*)(obj + 0x6e) > maxTime) {
                maxTime = *(ushort*)(obj + 0x6e);
            }

            // Set current object pointer
            *(int**)(this + 0x1e24) = obj;

            // Create animation controller for the object
            int* animController = createAnimationController(obj); // FUN_00673280
            *(int*)(*(int*)(slotBase + 0x4c) + loopIndex * 4) = animController;

            if (errorCode == 0) {
                *(int**)(this + 0x1e20) = animController;
                // Read transform data from slot (slot+0x20 and +0x28)
                __int64 transform0 = *(__int64*)(slotBase + 0x20);
                __int64 transform1 = *(__int64*)(slotBase + 0x28);
                setTransform(animController, *(int*)(this + 0x1e34), &transform0); // FUN_006735d0

                if (errorCode == 0) {
                    // Finalize the character
                    *(ushort*)(this + 0x1e1c) = slotIndex; // store ID
                    *(int*)(animController + 0x38) = this; // back pointer
                    *(int*)(animController + 0x3c) = &characterUpdateCallback; // FUN_006711e0

                    // Set bounding box or time range from stored data
                    *(short*)(*(int*)(animController + 0x180) + 0x60) = *(short*)(this + 0x1e28);
                    *(short*)(*(int*)(animController + 0x180) + 0x62) = *(short*)(this + 0x1e2a);

                    updateSystem(); // FUN_00674e10
                }
            }
        }
        // Increment child counter
        *(short*)(slotBase + 0x48) += 1;
        loopIndex--;
    }

    if (errorCode == 0) {
        // Set min/max time on the last character object's animation range
        int lastIdx = (short)numItems * 4;
        int* lastAnimObject = *(int**)(*(int*)(slotBase + 0x4c) + lastIdx - 4);
        *(ushort*)(lastAnimObject + 0x60) = (ushort)minTime;
        *(ushort*)(lastAnimObject + 0x62) = (ushort)maxTime;

        // Return the last animation controller
        *(int**)(this + 0x1e20) = lastAnimObject;
        return lastAnimObject;
    }
    return 0;
}