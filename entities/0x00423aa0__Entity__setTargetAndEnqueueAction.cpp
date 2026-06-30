// FUNC_NAME: Entity::setTargetAndEnqueueAction
void __fastcall Entity::setTargetAndEnqueueAction(Entity* thisPtr, int targetParam)
{
    // Access a thread-local state (e.g., g_bIsCutsceneActive, through FS segment)
    int* pTlsBase = *(int**)(*(int*)__readfsdword(0x2C) + 0x34);  // TEB +0x2C → pointer, deref twice +0x34
    int threadState = *pTlsBase;

    // Store the target parameter at offset 0xE0 (e.g., m_targetEntity or m_actionParam)
    *(int*)((uintptr_t)thisPtr + 0xE0) = targetParam;

    // If thread-local state is zero (e.g., not in a cutscene / UI blocking)
    if (threadState == 0)
    {
        // Global buffer/queue at DAT_01206880+0x14 is a dynamic list of (Entity*, targetParam) pairs
        int* pWritePos = *(int**)(DAT_01206880 + 0x14);  // pointer to current write position
        // Write vtable/sentinel pointer (PTR_LAB_0110b730) at the current position
        *(void**)pWritePos = (void*)&PTR_LAB_0110b730;
        pWritePos = (int*)((uintptr_t)pWritePos + 4);

        // Append this entity pointer
        *(void**)pWritePos = thisPtr;
        pWritePos = (int*)((uintptr_t)pWritePos + 4);

        // Append the target parameter
        *(int*)pWritePos = targetParam;
        pWritePos = (int*)((uintptr_t)pWritePos + 4);

        // Update global write pointer
        *(int**)(DAT_01206880 + 0x14) = pWritePos;
    }
}