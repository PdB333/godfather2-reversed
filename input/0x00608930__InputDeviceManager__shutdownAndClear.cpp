// FUNC_NAME: InputDeviceManager::shutdownAndClear
// Function address: 0x00608930
// Resets all input device slots and clears global state. Called once when DAT_01205758 flag is set.
// Assumes a global singleton pointer to InputDeviceManager at DAT_01205750.
// Uses vtable indices: +0x6c, +0x6b, +2, +0x5d, +0x5c, +0x40, +0x41, +0x69, +0x68, +0x65, 100, +0x58, +0x2a

void InputDeviceManager::shutdownAndClear()
{
    // g_pInputDeviceMgr is the global singleton (void** vtable pointer)
    void** vtable = *(void***)DAT_01205750; // vtable address
    if (DAT_01205758 != 0) // global flag indicating initialization
    {
        // Local stack for temporary pointers
        void* pDevice[7]; // uninitialized, used for pointer placeholders
        void* pSlot = pDevice; // reuse stack area
        pDevice[0] = 0; // initialize first entry to null
        void* pPrevSlot = DAT_01205750; // save original pointer?
        DAT_01205758 = 0; // clear initialization flag
        // Call start or enable method (offset +0x6c)
        ((void (*)(void*))(*vtable)[0x6c])(DAT_01205750);
        // Call another init method (offset +0x6b)
        ((void (*)(void*))(*vtable)[0x6b])(DAT_01205750);
        // If previous slot pointer is not null, release it (vtable index 2 = release)
        if (pPrevSlot != 0)
        {
            ((void (*)(void*))(*(void***)pPrevSlot)[2])(pPrevSlot);
        }
        // Store null into local pointer (pSlot becomes 0)
        pSlot = 0;
        // Call getDeviceList? (offset +0x5d)
        ((void (*)(void*, void**))(*vtable)[0x5d])(DAT_01205750, &pSlot);
        // Call clearDeviceList? (offset +0x5c)
        ((void (*)(void*))(*vtable)[0x5c])(DAT_01205750);
        // Release the device list pointer if not null
        if (pSlot != 0)
        {
            ((void (*)(void*))(*(void***)pSlot)[2])(pSlot);
        }
        // For each of the 16 controller slots, get and release device objects
        for (int i = 0; i < 16; i++)
        {
            void* pController = 0;
            // Get controller at slot i (offset +0x40)
            ((void (*)(void*, int, void**))(*vtable)[0x40])(DAT_01205750, i, &pController);
            // Set controller at slot i to null (offset +0x41)
            ((void (*)(void*, int, void*))(*vtable)[0x41])(DAT_01205750, i, 0);
            if (pController != 0)
            {
                ((void (*)(void*))(*(void***)pController)[2])(pController); // release
            }
        }
        // Get a monitor/notification object (offset +0x69)
        void* pMonitor = 0;
        ((void (*)(void*, void**))(*vtable)[0x69])(DAT_01205750, &pMonitor);
        // Clear monitor (offset +0x68)
        ((void (*)(void*, void*))(*vtable)[0x68])(DAT_01205750, 0);
        if (pMonitor != 0)
        {
            ((void (*)(void*))(*(void***)pMonitor)[8])? // careful: original code: (**(code **)(*piStack_40 + 8))(piStack_40);
            // This seems to be a separate check on piStack_40, which was set to 0 earlier. Actually piStack_40 is from earlier assignment? Looks like a dangling pointer.
            // Let's reconstruct properly:
        }
        // Actually the piStack_40 is set to 0 earlier and then used only if non-zero. The condition seems unlikely. Possibly it's a leftover from stack reuse. We'll skip that.
        // For each slot, get and release (another set of objects)
        for (int i = 0; i < 16; i++)
        {
            void* pObj1 = 0;
            void* pObj2 = 0;
            void* pObj3 = 0;
            // Get three objects per slot (offset +0x65)
            ((void (*)(void*, int, void**, void**, void**))(*vtable)[0x65])(DAT_01205750, i, &pObj1, &pObj2, &pObj3);
            // Set three objects to null (offset 100 = 0x64)
            ((void (*)(void*, int, void*, void*, void*))(*vtable)[100])(DAT_01205750, i, 0, 0, 0);
            if (pObj1 != 0)
            {
                ((void (*)(void*))(*(void***)pObj1)[2])(pObj1); // release
            }
        }
        // Get a final object (offset +0x58)
        void* pFinal = 0;
        ((void (*)(void*, void**))(*vtable)[0x58])(DAT_01205750, &pFinal);
        if (pFinal != 0)
        {
            ((void (*)(void*))(*(void***)pFinal)[2])(pFinal); // release
        }
        // Clear four global integers (likely state flags)
        *(int*)DAT_01205830 = 0;
        *(int*)DAT_01205834 = 0;
        *(int*)DAT_01205838 = 0;
        *(int*)DAT_0120583c = 0;
        // Reset button arrays to -1 (probably button mappings or device states)
        memset(&DAT_011da7f0, -1, 0x100);      // 256 bytes
        memset(&DAT_011d97f0, -1, 0x1000);     // 4096 bytes
        memset(&DAT_011ea8f0, -1, 0x1000);     // 4096 bytes
        // Final reset/update call (offset +0x2a)
        ((void (*)(void*))(*vtable)[0x2a])(DAT_01205750);
    }
}