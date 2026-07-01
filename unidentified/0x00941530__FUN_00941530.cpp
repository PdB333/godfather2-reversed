// FUNC_NAME: SomeClass::releaseResources
void __thiscall releaseResources(SomeClass *this) {
    // Release first object via manager's virtual method (likely unregister/remove)
    (*(void (__thiscall **)(uintptr_t, int))(*(int *)this->m_pManager + 4))(this->m_pObj1, 0);
    
    // Release second object if present
    if (this->m_pObj2 != 0) {
        (*(void (__thiscall **)(uintptr_t, int))(*(int *)this->m_pManager + 4))(this->m_pObj2, 0);
    }
    
    // Final cleanup on manager (e.g., flush, shutdown)
    (*(void (__thiscall **)(void))(*(int *)this->m_pManager + 0xC))();
}

// Struct layout:
// +0x00: m_pObj1 (uintptr_t) - first resource handle
// +0x0C: m_pObj2 (void*) - second resource (possibly null)
// +0x10: m_pManager (Manager*) - object with vtable at offset 0