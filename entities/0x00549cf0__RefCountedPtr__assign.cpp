// FUNC_NAME: RefCountedPtr::assign
void RefCountedPtr::assign(void* newPtr) {
    // m_pObject is at this+0xC0
    void* currentObj = this->m_pObject; 
    if (currentObj == newPtr) {
        return;
    }
    if (currentObj != nullptr) {
        // Object layout: +0 vtable, +4 refCountEnabled (short), +6 refCount (short)
        short* refCountEnabled = (short*)((int)currentObj + 4);
        short* refCount = (short*)((int)currentObj + 6);
        if (*refCountEnabled != 0) {
            *refCount = *refCount - 1;
            if (*refCount == 0) {
                // Call release function from vtable entry 0
                void (*release)(int) = *(void (**)(int))currentObj;
                release(1);
            }
        }
    }
    this->m_pObject = newPtr;
    if (newPtr != nullptr) {
        short* refCountEnabled = (short*)((int)newPtr + 4);
        short* refCount = (short*)((int)newPtr + 6);
        if (*refCountEnabled != 0) {
            *refCount = *refCount + 1;
        }
    }
}