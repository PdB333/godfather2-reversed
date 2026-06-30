// FUNC_NAME: EARSHandle::init
int EARSHandle::init(int* pManager, int sourceHandle)
{
    int* piVar2 = pManager;
    // Call manager's vtable+8 (likely addRef)
    pManager->vtable[2](pManager); // vtable+8 (index 2 = 8/4)
    int newHandle;
    if (sourceHandle != 0) {
        // Duplicate handle from sourceHandle via manager
        newHandle = createHandle(sourceHandle, piVar2);
    } else {
        newHandle = 0;
    }
    // Assign handle to this object's manager
    assignHandle(piVar2, newHandle);
    // Store manager pointer at offset +0x14
    this->m_pManager = pManager; // +0x14
    // Call addRef again (likely incremented for each reference)
    pManager->vtable[2](pManager);
    if (sourceHandle != 0) {
        // Create another handle copy (maybe for internal tracking)
        int tempHandle = createHandle(sourceHandle, this->m_pManager);
        this->m_handle = tempHandle; // +0x18
        // Release original source handle via manager (vtable+4)
        pManager->vtable[1](sourceHandle, 0); // vtable+4 (index 1 = 4/4)
        // Finalize/cleanup (vtable+12)
        pManager->vtable[3](); // vtable+12 (index 3 = 12/4)
        return this;
    }
    // If sourceHandle is zero, set handle to 0
    this->m_handle = 0; // +0x18
    // Finalize/cleanup
    pManager->vtable[3]();
    return this;
}