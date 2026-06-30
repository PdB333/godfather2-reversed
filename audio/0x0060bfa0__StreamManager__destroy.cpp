// FUNC_NAME: StreamManager::destroy
void __thiscall StreamManager::destroy(void) {
    // Global pointers (addresses from Ghidra)
    // DAT_01205750: pointer to AudioManager instance
    // DAT_0120583c: flag or active pointer
    // DAT_01205868: pointer to child resource manager
    int *pAudioMgr = (int *)DAT_01205750;
    int *pVtable = *(int **)this; // vtable pointer at +0x0
    int *pChild = *(int **)((char *)this + 4); // child pointer at +0x4

    if ((pAudioMgr != (int *)0x0) && (pVtable != (int *)0x0) && (pVtable == (int *)DAT_0120583c)) {
        // Clear the active pointer
        DAT_0120583c = 0;
        // Call AudioManager::release or stop at vtable+0x1a0 (method index 0x68)
        (*(void (**)(int *, int))(pAudioMgr[0] + 0x1a0))(pAudioMgr, 0);
    }

    // Call this object's destructor at vtable+8 (index 2)
    (*(void (**)(int *))(pVtable[8]))((int *)this);

    // Handle child resource
    if (pChild != (int *)0x0) {
        if (DAT_01205868 != (int *)0x0) {
            // Call child's vtable+4 (index 1) – likely a release or delete
            (*(void (**)(int *, int))(DAT_01205868[0] + 4))(pChild, 0);
        }
        // If child is not the same as this, clear child pointer
        if (this != (int *)pChild) {
            *(int **)((char *)this + 4) = 0;
        }
    }
}