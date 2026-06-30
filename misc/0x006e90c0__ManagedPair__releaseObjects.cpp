// FUNC_NAME: ManagedPair::releaseObjects
void __fastcall ManagedPair::releaseObjects(ManagedPair* thisPtr)
{
    // Call manager's release function (vtable +4) on first object with flag 0
    // Manager object is at offset 0x10 (thisPtr->m_pManager)
    // First object at offset 0x00 (thisPtr->m_pObj1)
    typedef void (__fastcall *ReleaseFunc)(void* obj, int flag);
    ReleaseFunc release = (ReleaseFunc)(*(int*)thisPtr->m_pManager + 4);
    release(thisPtr->m_pObj1, 0);

    // Second object at offset 0x0C (thisPtr->m_pObj2)
    if (thisPtr->m_pObj2 != nullptr) {
        release(thisPtr->m_pObj2, 0);
    }

    // Call manager's cleanup method (vtable +12) with no arguments
    typedef void (__fastcall *CleanupFunc)(void* manager);
    CleanupFunc cleanup = (CleanupFunc)(*(int*)thisPtr->m_pManager + 12);
    cleanup(thisPtr->m_pManager);
}