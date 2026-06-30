// FUN_004c8ae0: ResourceLoader::requestLoad
bool __thiscall ResourceLoader::requestLoad(void)
{
    bool bSuccess = false;
    // Check if the loader is initialized (likely a flag or pointer)
    if (*(int*)(this + 0x0C) != 0)
    {
        // Setup callback struct: first byte = 1 (possibly a request type or flags),
        // second word = pointer to a static completionHandler function (0x004c89c0)
        struct {
            byte   flags;     // +0x00
            void*  callback;  // +0x04
        } local_cb = { 1, (void*)0x004c89c0 };

        // Call the engine's resource loading function
        // g_pAssetManager (DAT_012234bc) is a global manager instance
        // this->m_resourceID (+0x10) is the identifier for the resource (e.g., name hash, file path)
        int handle = FUN_005e4f90(DAT_012234bc, *(int*)(this + 0x10), &local_cb);
        // Store the returned handle (e.g., resource slot index, pointer)
        *(int*)(this + 0x14) = handle;
        if (handle != 0)
        {
            bSuccess = true;
        }
    }
    return bSuccess;
}