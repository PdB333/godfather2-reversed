// FUNC_NAME: createGlobalStreamRecord
void createGlobalStreamRecord(void* pManager, int resourceID)
{
    // Allocate a record of 0x14 bytes (20 bytes) - likely a stream handle record
    unsigned int* pRecord = (unsigned int*)AllocateMemory(0x14);
    if (pRecord != (unsigned int*)0x0) {
        pRecord[4] = resourceID;            // +0x10: store resource ID
        pRecord[0] = (unsigned int)pManager; // +0x00: store manager pointer
        // Setup an allocation request structure: type=2, size=0x10, flags=0
        int request[3];
        request[0] = 2;      // request type
        request[1] = 0x10;   // requested size
        request[2] = 0;      // flags

        // Call the virtual function at vtable[0] on the manager (likely a stream creation method)
        unsigned int result = ((unsigned int (*)(void*, int*))(*(void***)pManager)[0])(pManager, request);
        pRecord[2] = result; // +0x08: store result low
        pRecord[3] = result; // +0x0C: store result high (duplicated, possibly for 64-bit alignment)
        pRecord[1] = 0;      // +0x04: clear field

        // Store pointer to the record in the global variable
        g_pGlobalStreamRecord = pRecord;
        return;
    }
    g_pGlobalStreamRecord = (unsigned int*)0x0;
}