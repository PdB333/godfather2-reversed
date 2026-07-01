// FUNC_NAME: SomeManager::constructor
void __fastcall SomeManager::constructor(SomeManager* thisObj)
{
    // Set initial vtable pointers (base class)
    thisObj->vtable0 = &PTR_FUN_00d7468c;   // +0x00: first vtable
    thisObj->vtable3 = &PTR_LAB_00d74670;   // +0x0C: second vtable (offset 12)

    // Check if there is an existing global manager instance
    if (g_pOldManager != nullptr && g_pOldManager != (SomeManager*)0x48) // 0x48 sentinel?
    {
        // Cleanup the old manager
        cleanupOldManager();

        if (g_pOldManager != nullptr)
        {
            // Get the actual object pointer (adjusting for offset 0x48)
            SomeManager* oldObj = (SomeManager*)((uint8_t*)g_pOldManager - 0x48);
            if (oldObj != nullptr)
            {
                // Call virtual destructor (first vtable entry) with argument 1
                (oldObj->vtable0->destructor)(1);
            }
            if (g_pOldManager != nullptr)
            {
                // Deallocate memory
                operator delete(&g_pOldManager);
                g_pOldManager = nullptr;
            }
        }
    }

    // Update vtable pointers to derived class
    thisObj->vtable3 = &PTR_LAB_00d745c0;   // +0x0C: new second vtable
    thisObj->vtable0 = &PTR_LAB_00d74620;   // +0x00: new first vtable
}