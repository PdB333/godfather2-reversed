// FUNC_NAME: NPCInfoManager::registerShowNPCInfoCommand
void __thiscall NPCInfoManager::registerShowNPCInfoCommand(NPCInfoManager* this, CommandManager* cmdMgr, void* param_2)
{
    // Set flag at offset 0x100 to indicate active/initialized
    *(int*)(this + 0x100) = 1;

    // Get display name from command manager's vtable (likely a virtual method to get command name)
    // The vtable is at *cmdMgr, offset 0x1d4 (could be GetDisplayName)
    char** namePtr;
    namePtr = (char**)((*(code**)(*(int*)cmdMgr + 0x1d4))());  // returns pointer to a string pointer
    char* name;
    if (*namePtr == 0) {
        name = &DAT_0120546e;  // fallback name string
    } else {
        name = *namePtr;
    }

    // Copy name into local buffer (this+0x108) with max length 0x80
    // FUN_005c4660 is likely strncpy or similar
    strncpy((char*)(this + 0x108), name, 0x80);  // assume 4th param is unused or flags

    // Call initialization routine for command manager (maybe setup callback)
    FUN_0093ad10(cmdMgr);

    // Insert this object into a linked list managed by cmdMgr
    // cmdMgr+0x48 is the head pointer field, cmdMgr[0x13] is tail (0x4c)
    int** headField = (int**)(((int)cmdMgr) + 0x48);  // offset 0x12 in int units = 0x48 bytes
    int** currentHead = (int**)(this + 0x114);        // this's prev pointer at +0x114
    if (*currentHead != headField) {
        // If we have an old head pointer, free it? (likely linked list node)
        if (*currentHead != 0) {
            FUN_004daf90(currentHead);  // free current node
        }
        *currentHead = (int*)headField;  // set prev to point to head field address
        if (headField != 0) {
            this->next = (int*)cmdMgr->tail;  // this->next at +0x118
            cmdMgr->tail = (int)currentHead;  // update tail to point to this->prev
        }
    }

    // Clear or free any auxiliary data at +0x11c
    if (*(int*)(this + 0x11c) != 0) {
        FUN_004daf90((undefined4*)(this + 0x11c));
        *(int*)(this + 0x11c) = 0;
    }

    // Set another flag at +0x104 to 0
    *(int*)(this + 0x104) = 0;

    // Set a bit flag (0x800) at +0x5c (likely a public toggle)
    *(int*)(this + 0x5c) |= 0x800;

    // Register a console command "ShowNPCInfo" with callback?
    // FUN_005a04a0 might be RegisterConsoleCommand("ShowNPCInfo", 0, &someCallback, 0)
    FUN_005a04a0("ShowNPCInfo", 0, &DAT_00d8a64c, 0);

    return;
}