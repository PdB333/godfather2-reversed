// FUNC_NAME: SomeClass::~SomeClass
void SomeClass::~SomeClass() {
    // If the resource pointer at this+0x20 is non-null, release it
    if (this->m_pResource != nullptr) {
        releaseResource(this->m_pResource); // FUN_009c8f10 – deallocates or releases the resource
    }

    // Restore vtable pointer at this+0x14 to the base class vtable (prevents virtual calls during destruction)
    this->vtable = g_BaseVTable; // PTR_LAB_00e40f38

    // Clear a global flag
    g_globalFlag = 0; // _DAT_01223558

    // Call base class destructors (likely two-step destruction)
    BaseClass1::~BaseClass1(); // FUN_004083d0
    BaseClass2::~BaseClass2(); // FUN_0049c640
}