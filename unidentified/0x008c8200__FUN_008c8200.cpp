// FUNC_NAME: SomeManager::update
void __fastcall SomeManager::update(int this) {
    // Check if a pointer at +0x8 is non-null (e.g., mActive or mData)
    if (*(int*)(this + 8) != 0) {
        // Get a manager instance (e.g., singleton)
        int* pMgr = FUN_00791300(); // getManagerInstance()
        if (pMgr != 0) {
            // Get the same instance again? Possibly a different call?
            pMgr = FUN_00791300(); // getManagerInstance() again
            // Process a member at offset +0x3c of the manager
            FUN_004088c0(pMgr + 0x3c); // processManagerData(pMgr->someMember)
        }
    }
}