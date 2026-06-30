// FUNC_NAME: HandleManager::RegisterHandle
void HandleManager::RegisterHandle(int* outHandle, const HandleData* data) {
    int& handle = *outHandle;
    if (handle >= 0) {
        // Update existing entry
        *(uint64_t*)(&g_Keys[handle * 3]) = *(uint64_t*)&data->field_0;
        *(uint64_t*)(&g_Values[handle * 3]) = *(uint64_t*)&data->field_8;
        *(uint64_t*)(&g_Extras[handle * 6]) = *(uint64_t*)&data->field_16;
        return;
    }

    // Try to allocate a new handle
    if (g_NumHandles < 31 && data->field_4 != 0) {
        int index = 0;
        uint64_t* entry = &g_Keys[0];
        uint offset = 0;
        do {
            if (offset > 0x2FF) break;  // safety limit
            if (*(int*)(entry + 1) == 0) { // second word free?
                *entry = *(uint64_t*)&data->field_0;
                entry[1] = *(uint64_t*)&data->field_8;
                *(int*)(entry + 2) = *(int*)&data->field_16;
                *(int*)((char*)entry + 0x14) = *(int*)((char*)data + 0x14);
                handle = index;
                g_NumHandles++;
            }
            index++;
            offset += 0x18;
            entry += 3;  // each handle occupies 3 uint64_t slots
        } while (handle < 0);
    }

    // Register handle type
    if (handle >= 0 && g_NumTypes < 31) {
        int typeIndex = 0;
        uint offset = 0x4A0;  // offset to type table start
        do {
            if (*(int*)((char*)&g_Keys + offset) == *(int*)(&g_Values[handle * 3])) {
                // Match found - increment count for this type
                g_TypeCounts[typeIndex]++;
                g_HandleTypes[handle] = typeIndex;
                return;
            }
            offset += 8;
            typeIndex++;
        } while (offset < 0x4D0);

        typeIndex = 0;
        offset = 0x4A0;
        do {
            if (*(int*)((char*)&g_Keys + offset) == 0) {
                // Empty slot - add new type
                g_TypeCounts[typeIndex] = 1;
                g_TypeKeys[typeIndex] = *(int*)(&g_Values[handle * 3]);
                g_HandleTypes[handle] = typeIndex;
                g_HandleFlags[handle] = 0;
                if (*(uint*)((char*)data + 0xC) & 0x01000000) {
                    g_HandleFlags[handle] = *(int*)(&g_Extras[handle * 6]);
                }
                g_NumTypes++;
                return;
            }
            offset += 8;
            typeIndex++;
        } while (offset < 0x4D0);
    }
}