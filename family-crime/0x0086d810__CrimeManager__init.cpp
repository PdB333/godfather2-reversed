// FUNC_NAME: CrimeManager::init
void __thiscall CrimeManager::init(CrimeManager* this)
{
    // Set first vtable pointer at offset 0x00
    this->vtable1 = &PTR_LAB_00d75f7c;
    // Set second vtable pointer at offset 0x60 (0x18 * 4)
    this->secondVtable = &PTR_LAB_00d75f68;

    // Check if already initialized (offset +0x5C)
    if (this->mInitialized != 0)
    {
        // Verify global manager state via g_globalManager (DAT_01131018)
        if (isGlobalInitialized(g_globalManager) != 0)
        {
            // Destroy the subobject at offset +0x60 (the second base)
            destroySecondBase(&this->secondBase);
        }
    }

    // Finalize initialization
    finalizeInitialization();
}