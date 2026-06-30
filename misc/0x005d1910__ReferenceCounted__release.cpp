// FUNC_NAME: ReferenceCounted::release
void ReferenceCounted::release()
{
    int *pBlock = this->m_pData;            // +0x00: pointer to reference-counted block
    this->m_refCount1 = 0;                  // +0x04: first reference counter
    this->m_refCount2 = 0;                  // +0x08: second reference counter (unused?)
    if (pBlock != 0) {
        // Free the block with a destructor callback (block header at offset -4 contains reference count)
        g_pMemoryAllocator->freeWithDestructor(pBlock, 0x10, *(uint *)(pBlock - 4), &LAB_005bddd0);
        // Attempt to decrement the reference count; if it reaches zero, call full destructor
        if (!ReferenceCounted::atomicDecrement((int *)(pBlock - 4))) {
            // Call vtable destructor via global factory (DAT_012234ec is a singleton)
            (*(void (__thiscall **)(int, int))(**(int **)(DAT_012234ec + 4) + 4))(pBlock - 4, 0);
        }
        this->m_pData = 0;
        return;
    }
    this->m_pData = 0;
}