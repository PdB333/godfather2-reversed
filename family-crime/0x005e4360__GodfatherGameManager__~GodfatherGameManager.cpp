// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager

void __thiscall GodfatherGameManager::destructor(void) {
    // Set vtable to a special placeholder/destructor VTBL to avoid virtual calls
    this->vtablePtr = &gDestructorVTBL1;

    // If the managed object exists, call its destructor via vtable+0x0C
    if (this->m_pSomeManager != nullptr) {
        (*(void (**)(void))(*(uint32_t *)this->m_pSomeManager + 12))();
    }

    // Free three lists/arrays if they exist
    if (this->m_pList1 != 0) {
        MemFree(this->m_pList1);
    }
    if (this->m_pList2 != 0) {
        MemFree(this->m_pList2);
    }
    if (this->m_pList3 != 0) {
        MemFree(this->m_pList3);
    }

    // Reset global singleton flag
    gGameManagerActive = 0;

    // Restore vtable to a static placeholder (or base class VTBL)
    this->vtablePtr = &gStaticPlaceholderVTBL;
}

// Offsets relative to this (multiply by 4 for byte offsets):
// this->vtablePtr         +0x0000
// this->m_pSomeManager    +0x6010  (0x1804)
// this->m_pList3          +0x6014  (0x1805)
// this->m_pList2          +0x6020  (0x1808)
// this->m_pList1          +0x602C  (0x180b)
// gGameManagerActive is a global at 0x012234bc