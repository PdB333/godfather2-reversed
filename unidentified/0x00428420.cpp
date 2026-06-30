// FUN_NAME: ClassRegistry::registerClassVtable
void ClassRegistry::registerClassVtable()
{
    // Access thread-local storage to determine current thread's initialization state
    // FS:[0x2C] holds TLS directory pointer; offset 0x34 is per-thread registration flag
    int* tlsData = *(int**)__readfsdword(0x2C);
    int* pThreadFlag = (int*)((char*)tlsData + 0x34);

    if (*pThreadFlag == 0)
    {
        // Retrieve global pointer to the next available vtable slot in the class registry
        // g_ClassRegistry is a structure at 0x01206880; offset 0x14 contains a pointer
        // to the current insertion point in an array of vtable entries (each 4 bytes)
        void*** pCurrentSlot = (void***)(0x01206880 + 0x14);

        // Store the vtable address for this class (0x0110b770) at the current slot
        **pCurrentSlot = (void*)&g_classVtable_0110b770;

        // Advance the registry pointer to the next slot (move by 4 bytes)
        *pCurrentSlot = (void**)((char*)(*pCurrentSlot) + 4);
    }
    else
    {
        // Thread already registered – set global readiness flag
        g_bRegistryReady = 1;
    }
}