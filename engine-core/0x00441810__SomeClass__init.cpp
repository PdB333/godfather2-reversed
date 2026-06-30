// FUNC_NAME: SomeClass::init
void SomeClass::init(SomeObject* pObj, int hResource) {
    // Store object pointer at offset 0x00 (m_pObject)
    this->m_pObject = pObj;

    // Call virtual function at vtable+0x08 (presumed preInit method)
    pObj->vfunc3();

    if (hResource != 0) {
        // Allocate handle and store at offset 0x04 (m_handle)
        this->m_handle = createHandle(hResource, pObj);

        // Call virtual function at vtable+0x04 (presumed attachHandle) with (hResource, 0)
        pObj->vfunc2(hResource, 0);
    } else {
        // Clear handle if no resource provided
        this->m_handle = 0;
    }

    // Always call virtual function at vtable+0x0C (presumed finalizeInit)
    pObj->vfunc4();
}