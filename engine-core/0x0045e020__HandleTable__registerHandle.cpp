// FUNC_NAME: HandleTable::registerHandle
void HandleTable::registerHandle(int newHandle) {
    // this = ESI
    // newHandle passed in EAX
    uint32_t* handleArray = (uint32_t*)((uint8_t*)this + 0x90);       // m_handles[8]
    uint32_t* priorityArray = (uint32_t*)((uint8_t*)this + 0x240);    // m_priorities[8] (or timestamps)

    int bestSlot = 0;          // uVar5
    int bestOffset = 0;        // iVar4

    if (newHandle == 0) {
        return;
    }

    // Virtual call to generate a new resource ID (e.g., allocate a handle)
    int resourceId = (*(int (__thiscall**)(HandleTable*))((uint8_t*)this + 0xac))(this);
    if (resourceId == 0) {
        return;
    }

    // Search for an empty slot first
    for (int i = 0; i < 8; i++) {
        if (handleArray[i] == 0) {
            handleArray[i] = resourceId;
            return;
        }
    }

    // No empty slot; find a slot to replace (apparently based on comparing 
    // handle with associated priority; the exact logic is unclear from decompilation)
    for (int i = 0; i < 8; i++) {
        // Compare handle with priority at same index (or some related value)
        // The decompiled code shows: if (handleArray[i] < *(priorityArray + bestOffset???)
        // but the pointer arithmetic is messy. This is a best-effort reconstruction.
        if (handleArray[i] < priorityArray[i]) {
            bestSlot = i;
            // bestOffset computed as (handleArray + i) - (priorityArray)
            bestOffset = (int)(&handleArray[i]) - (int)(priorityArray);
        }
    }

    // Cleanup the old resource if its handle is in a certain range
    uint16_t oldHandleLow = (uint16_t)(handleArray[bestSlot] & 0xFFFF);
    if (oldHandleLow < 0x200) {
        // Global handle-to-object table (size 0x30 per entry, offset 0x10 into each entry)
        uint8_t* globalTable = DAT_012234bc; // global pointer
        uint8_t* entry = globalTable + oldHandleLow * 0x30 + 0x10;
        if (entry != nullptr && *(uint32_t*)(entry + 0x2C) == handleArray[bestSlot] && entry != 0) {
            *(uint32_t*)(entry + 0x24) = 0; // clear some fields
            *(uint32_t*)(entry + 0x28) = 0;
        }
    }

    // Replace the old handle with the new resource ID
    handleArray[bestSlot] = resourceId;
}