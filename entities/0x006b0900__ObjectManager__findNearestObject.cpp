// FUNC_NAME: ObjectManager::findNearestObject
float __thiscall ObjectManager::findNearestObject(const float* position, int* outObject, int filterType, int filterSubtype, bool strictMatch) {
    // Container metadata: count at +0x38, pointer to buffer at +0x34 (buffer has header of 12 bytes, then array of Entity*)
    int count = *(int*)(this + 0x38);
    int* arrayBase = *(int**)(this + 0x34) + 3; // +0x3 ints = +0xc offset
    int bestEntity = 0;
    float bestDistSq = 1e30f; // Large initial value (replaces DAT_00d5ccf8)

    for (int i = 0; i < count; i++) {
        int entityPtr = arrayBase[i];
        if (entityPtr != 0) {
            int* filterData = *(int**)(entityPtr + 0xfc); // Pointer to filter data block at +0xfc
            if (filterData != 0) {
                // Filter by type (param_4) and subtype (param_5)
                bool typeMatch = false;
                if (filterType == 0 || filterType == *(int*)(filterData + 0x14)) {
                    typeMatch = true;
                } else if (!strictMatch) {
                    continue;
                }

                // Subtype filter
                bool subtypeMatch = (filterSubtype == 0 || filterSubtype == *(int*)(filterData + 0x18));
                if (!subtypeMatch && !(strictMatch && typeMatch)) {
                    continue;
                }

                // Compute squared distance to entity position (+0x10, +0x14, +0x18)
                float dx = position[0] - *(float*)(entityPtr + 0x10);
                float dy = position[1] - *(float*)(entityPtr + 0x14);
                float dz = position[2] - *(float*)(entityPtr + 0x18);
                float distSq = dx*dx + dy*dy + dz*dz;

                if (distSq < bestDistSq || bestEntity == 0) {
                    bestDistSq = distSq;
                    bestEntity = entityPtr;
                }
            }
        }
    }

    if (outObject != 0) {
        *outObject = bestEntity;
    }
    return bestDistSq;
}