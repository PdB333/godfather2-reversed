// FUNC_NAME: SomeClass::getFlagFromPointerChain
void __thiscall SomeClass::getFlagFromPointerChain(unsigned char *outFlag) {
    *outFlag = 0;
    // Check primary pointer stored at this+0x00
    if (this->m_pPrimary != nullptr) {
        // Dereference to get secondary struct, then read pointer at offset 0x10 within it
        void *pSecondaryPtr = *(void **)((unsigned char *)this->m_pPrimary + 0x10);
        if (pSecondaryPtr != nullptr) {
            // FUN_004eaec0 likely fills outFlag based on pSecondaryPtr
            this->helperGetFlag(pSecondaryPtr, outFlag);
        }
    }
}