// FUNC_NAME: RefCountedObject::release
void RefCountedObject::release()
{
    // Acquire lock or synchronize (FUN_005a72f0)
    syncLock();

    // Check if reference count at offset+2 is zero (indicates no more references)
    if (*(short*)(this + 2) == 0)
    {
        // Get the owning manager/singleton (FUN_005a3ae0)
        Manager* mgr = getManager();

        // Release member object at mgr+0x4c
        if (mgr->member1 != nullptr)
        {
            // Call vtable destructor via dispatch table at DAT_0103aee0
            (**(code**)(&g_dispatchTable + (mgr->member1->vtableIndex & 0x7fff) * 4))(mgr->member1);
        }
        mgr->member1 = nullptr;
        mgr->someFlag = 0;  // clear offset 0x54

        // Release member object at mgr+0x58
        if (mgr->member2 != nullptr)
        {
            (**(code**)(&g_dispatchTable + (mgr->member2->vtableIndex & 0x7fff) * 4))(mgr->member2);
        }
        mgr->member2 = nullptr;

        // Post-release cleanup (FUN_005ba710)
        postReleaseCleanup();

        // Deallocate this object (size 0x5c) via global deallocator
        (*g_deallocFunc)(this, 0x5c);
    }
}