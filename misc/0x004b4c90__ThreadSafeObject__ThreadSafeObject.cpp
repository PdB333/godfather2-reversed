// FUNC_NAME: ThreadSafeObject::ThreadSafeObject
ThreadSafeObject * __thiscall ThreadSafeObject::ThreadSafeObject(ThreadSafeObject *this, void *somePointer1, void *somePointer2, void *somePointer3) {
    // +0x00: vtable pointer (most derived)
    // +0x04: base class vtable pointer (temporarily set for base construct, then overridden)
    // +0x08: flags (int) - set to 1
    // +0x0C: m_param2 (void*) - somePointer1
    // +0x10: m_param3 (void*) - somePointer2
    // +0x14: m_param5 (void*) - somePointer3
    // +0x18: m_zero (int) - initialized to 0
    // +0x1C: padding (aligns critical section to 8 bytes)
    // +0x20: m_criticalSection (CRITICAL_SECTION)

    // Set base vtable temporarily (for base class constructor)
    this->baseVtable = &PTR_LAB_00e362b8;
    // Set flags
    this->flags = 1;
    // Set derived vtable
    this->vtable = &PTR_FUN_00e35888;
    // Override base vtable with final derived class vtable
    this->baseVtable = &PTR_LAB_00e358a4;
    // Store parameters
    this->m_param2 = somePointer1;
    this->m_param3 = somePointer2;
    this->m_param5 = somePointer3;
    // Initialize zero field
    this->m_zero = 0;
    // Initialize critical section for thread safety
    InitializeCriticalSection(&this->m_criticalSection);
    // Call base class constructor (passes somePointer2 - likely a reference to a shared object)
    SomeBase::SomeBase(somePointer2);
    return this;
}