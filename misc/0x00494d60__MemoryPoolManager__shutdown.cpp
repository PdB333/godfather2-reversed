// FUNC_NAME: MemoryPoolManager::shutdown
void MemoryPoolManager::shutdown()
{
    int temp;
    undefined4* node;
    undefined4 vtableArg;
    bool anyRemoved;
    undefined4* nextNode;
    int* item;
    int* otherItem;

    // Manager is a global singleton at DAT_012234a8
    MemoryPoolManager* manager = reinterpret_cast<MemoryPoolManager*>(DAT_012234a8);
    
    // Process first linked list (head at offset +0x10)
    temp = manager->firstListHead; // +0x04? Actually manager[4] is field at +0x10
    while (temp != 0) {
        node = reinterpret_cast<undefined4*>(manager->firstListHead); // +0x10
        if (node != nullptr) {
            if (reinterpret_cast<undefined4*>(manager->firstListTail) == node) { // +0x14
                manager->firstListTail = 0;
            }
            manager->firstListHead = *node;
        }
        temp = manager->firstListHead;
    }

    // Process second linked list (head at offset +0x5C)
    temp = manager->secondListHead; // +0x5C
    while (temp != 0) {
        item = reinterpret_cast<int*>(manager->secondListHead);
        otherItem = nullptr;
        if (item != nullptr) {
            temp = *item;
            manager->secondListHead = temp;
            otherItem = item;
            if (temp == 0) {
                manager->secondListTail = 0; // +0x60
            } else {
                *(undefined4*)(temp + 4) = 0;
                *item = 0;
            }
        }
        debugPrint(); // FUN_00abd5c0
        DeleteCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(otherItem + 0x3a)); // offset +0xE8
        if (otherItem[0x36] != 0) { // offset +0xD8
            freeMemory(otherItem[0x36]); // FUN_009c8f10
        }
        temp = manager->secondListHead;
    }

    // Drain a queue/flush buffer
    do {
        anyRemoved = false;
        EnterCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(manager + 10)); // offset +0x28
        if (manager->pendingCount != 0) { // +0x24
            manager->pendingIndex = manager->pendingIndex + 1; // +0x20
            if (static_cast<int>(manager->pendingMax) <= static_cast<int>(manager->pendingIndex)) { // +0x1C
                manager->pendingIndex = 0;
            }
            manager->pendingCount = manager->pendingCount - 1;
            anyRemoved = true;
        }
        LeaveCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(manager + 10));
    } while (anyRemoved);

    // Virtual calls for final cleanup
    vtableArg = manager->someVtableArg; // +0x08
    (manager->vtable[0])(0); // virtual function at index 0
    int* someManager = reinterpret_cast<int*>(getSomeManager()); // FUN_009c8f80
    (reinterpret_cast<void(__thiscall*)(int, int)>(someManager[1]))(vtableArg, 0); // virtual at offset 4
}