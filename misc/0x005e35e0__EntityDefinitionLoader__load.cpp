// FUNC_NAME: EntityDefinitionLoader::load
bool __thiscall EntityDefinitionLoader::load(byte* buffer) {
    bool success = true;
    if (buffer == nullptr) {
        return false;
    }
    uint32_t* header = (uint32_t*)buffer;
    if (*header != 0xB) {
        return true; // not our type, accept by default?
    }

    uint32_t numAnimations = header[1];   // +0x04
    uint32_t numModels     = header[2];   // +0x08
    uint32_t numEffects    = header[3];   // +0x0C
    uint32_t numFinalObj   = header[4];   // +0x10, count for a single object at end? Only 0 or 1

    int offset = 0x14; // start of variable-length arrays

    // Process animation array (each 100 bytes)
    for (uint32_t i = 0; i < numAnimations; i++) {
        byte* animData = buffer + offset;
        offset += 100;
        if (animData == nullptr) {
            success = false;
        } else {
            if (!FUN_005dc510(g_animationManager, animData)) {
                success = false;
            }
        }
    }

    // Process model array (each 40 bytes) and store pointers into dynamic array at g_modelManager
    for (uint32_t i = 0; i < numModels; i++) {
        byte* modelData = buffer + offset;
        offset += 0x28;
        if (modelData == nullptr) {
            success = false;
        } else {
            // Push back into a vector: g_modelManager is a manager with internal dynamic array
            int* vector = (int*)(g_modelManager + 0x24C); // +0x24C: pointer to array start?
            int* capacityAddr = (int*)(g_modelManager + 0x250);
            int* sizeAddr = (int*)(g_modelManager + 0x254);
            int capacity = *capacityAddr;
            int size = *sizeAddr;

            if (size == capacity) {
                int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
                FUN_005f0dc0(newCapacity); // reallocate/resize
                // update pointers after realloc
                capacity = *capacityAddr;
                size = *sizeAddr;
            }

            int* arrayStart = *(int**)(g_modelManager + 0x24C);
            arrayStart[size] = (int)modelData;
            *(int*)(g_modelManager + 0x254) = size + 1;
        }
    }

    if (!FUN_005f0720(g_modelManager)) {
        success = false;
    }

    // Process effects array (each 176 bytes)
    for (uint32_t i = 0; i < numEffects; i++) {
        byte* effectData = buffer + offset;
        offset += 0xB0;
        if (effectData == nullptr) {
            success = false;
        } else {
            FUN_004c9690(effectData);
        }
    }

    // Process final single object (e.g., a composite definition)
    if (numFinalObj != 0) {
        byte* finalData = buffer + offset;
        if (finalData == nullptr) {
            success = false;
        } else {
            if (!FUN_005de470(g_animationManager + 0x48, finalData)) {
                success = false;
            }
        }
    }

    // Finalize via virtual function
    (*(void(__thiscall**)(EntityDefinitionLoader*))(*DAT_01223510 + 0xD0))(DAT_01223510);
    return success;
}