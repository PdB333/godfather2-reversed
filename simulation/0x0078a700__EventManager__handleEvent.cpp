// FUNC_NAME: EventManager::handleEvent
void __thiscall EventManager::handleEvent(void* this, void* arg) {
    int* vtablePtr;
    int* pArg = &arg;
    int unusedLocal; // Possibly from a register - not initialized in decompiled code

    // Check if arg has a valid type identifier at offset 0xc
    if (*(int*)((char*)arg + 0xc) != 0 && *(int*)((char*)arg + 0xc) != 0x48) {
        // If the type identifier is zero, vtable is null
        if (*(int*)((char*)arg + 0xc) == 0) {
            vtablePtr = nullptr;
        } else {
            // Subtract 0x48 from the pointer at offset 0xc to get the object's vtable
            vtablePtr = (int*)(*(int*)((char*)arg + 0xc) - 0x48);
        }

        arg = nullptr; // Clear original pointer? Possibly to avoid reuse
        // Call a virtual function (index 4) on the object with a hash (0x383225a1)
        char result = ((char (*)(int))(*vtablePtr)[4])(0x383225a1);
        if (result != '\0' && unusedLocal != 0) {
            // Unknown function call (possibly debug output)
            FUN_00471610();
            // Virtual call on a member (this+0x4c) at vtable offset 0x28c (index 0x28c/4 = 0xA3)
            (**(void (***)(void))((char*)this + 0x4c) + 0x28c)();
            // Likely a debug print with the original arg pointer (now containing 0)
            FUN_00408a00(&pArg, 0);
        }
    }
}