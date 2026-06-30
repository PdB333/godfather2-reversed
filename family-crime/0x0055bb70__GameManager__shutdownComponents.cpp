// FUNC_NAME: GameManager::shutdownComponents
void __fastcall GameManager::shutdownComponents(GameManager* this)
{
    // Set initialized flag to false (offset +0x484)
    this->m_bInitialized = 0;

    // Free each of the four component pointers (offsets +0x710, +0x714, +0x718, +0x71c)
    for (int i = 0; i < 4; i++) {
        int* pComponent = *(int**)((uint8_t*)this + 0x710 + i * 4);
        if (pComponent != nullptr) {
            // Global pool manager at DAT_01206880 (likely ObjectManager)
            GlobalPoolManager* poolMgr = *(GlobalPoolManager**)DAT_01206880;
            uint8_t** freeListCursor = (uint8_t**)&poolMgr->freeList; // +0x14

            // Write sentinel vtable (freed marker)
            **(void***)freeListCursor = &FREED_VTABLE; // PTR_LAB_01124690

            // Advance cursor and store the component pointer
            (*freeListCursor) += 4;
            *(int*)*freeListCursor = (int)pComponent;

            // Advance and store back-pointer to owner's sub-object array (offset +0x54)
            (*freeListCursor) += 4;
            *(int*)*freeListCursor = (int)(this + 0x54); // Address of sub-object list root

            // Advance and store flag (1 = freed)
            (*freeListCursor) += 4;
            *(uint8_t*)*freeListCursor = 1;

            // Align cursor to DWORD boundary
            (*freeListCursor) += 4;
            *freeListCursor = (uint8_t*)(((uint32_t)*freeListCursor) & 0xFFFFFFFC);
        }
    }
}