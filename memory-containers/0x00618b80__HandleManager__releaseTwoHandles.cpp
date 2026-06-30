// FUNC_NAME: HandleManager::releaseTwoHandles
void __fastcall HandleManager::releaseTwoHandles(uint handle1, uint handle2)
{
    // Handle table entry: 0x38 bytes per entry
    // offset +0x14: pointer to resource (int*)
    HandleTableEntry* entry1 = nullptr;  // puVar1
    HandleTableEntry* entry2 = nullptr;  // puVar2

    // Validate handle range (max 0x1000 entries)
    if (handle1 < 0x1000)
        entry1 = &g_handleTable[handle1];  // DAT_011a0f28
    if (handle2 < 0x1000)
        entry2 = &g_handleTable[handle2];

    // Stack-based temporary object (possibly a smart pointer/pair)
    TempCleanupObject tempObject;  // iStack_14/puStack_10
    tempObject.vtable = nullptr;

    // Release first resource via virtual function at vtable+0x48
    if (entry1 && entry1->resourcePtr)
    {
        entry1->resourcePtr->release();  // vtable[0x48]
    }

    // Release second resource via virtual function at vtable+0x48
    if (entry2 && entry2->resourcePtr)
    {
        entry2->resourcePtr->release();  // vtable[0x48]
    }

    // Cleanup temporary object if it was allocated
    if (tempObject.vtable != nullptr)
    {
        // Call destructor at vtable+8
        tempObject.destroy();
    }
}