// FUNC_NAME: BNKStreamManager::registerBank
void __thiscall BNKStreamManager::registerBank(void* this) {
    // +0x4a: flags (ushort), bit 1 indicates already registered
    if ((*(unsigned short*)((int)this + 0x4a) & 2) == 0) {
        // +0x10: pointer to vtable or interface
        // +0x04: virtual function that returns something (likely a stream ID)
        auto virtualFunc = *(int (__stdcall **)())(*(int*)((int)this + 0x10) + 4);
        *(unsigned char*)((int)this + 0x49) = 1;
        *(unsigned char*)((int)this + 0x48) = 0;
        int streamHandle = virtualFunc();
        *(int*)((int)this + 0x44) = streamHandle;

        // Global stream manager? (DAT_00e3e658)
        int result = FUN_005c0830(&DAT_00e3e658);
        if (result < 0) {
            // +0x18: current count, +0x1c: capacity
            int* countPtr = (int*)((int)this + 0x18);
            int newCount = *countPtr + 1;
            if (*(int*)((int)this + 0x1c) < newCount) {
                // Grow array: FUN_005c27a0(ptr, newSize, elementSize, &ptr, &capacity)
                int newArray = FUN_005c27a0(*(int*)((int)this + 0x14), newCount, 0x18, countPtr, (int)this + 0x1c);
                *(int*)((int)this + 0x14) = newArray;
            }
            // Entry structure (0x18 bytes)
            struct Entry {
                char field0[4]; // 0x00: pointer to DAT_00e3e658
                char field4[4]; // 0x04: pointer to DAT_0120565c
                char field8[4]; // 0x08: 0
                char fieldC[4]; // 0x0C: callback (LAB_005bfd90)
                char field10[4]; // 0x10: 0
                char field14[4]; // 0x14: 1
            };
            Entry* entry = (Entry*)(*(int*)((int)this + 0x14) + *countPtr * 0x18);
            *countPtr = newCount;
            entry->field0 = (char*)&DAT_00e3e658;
            entry->field4 = (char*)&DAT_0120565c;
            *(int*)entry->field8 = 0;
            *(int*)entry->fieldC = (int)&LAB_005bfd90;
            *(int*)entry->field10 = 0;
            *(int*)entry->field14 = 1;
        }
        FUN_005c0890();
        // Mark as registered
        *(unsigned short*)((int)this + 0x4a) |= 2;
    }
}