// FUNC_NAME: EARSObject::init
void __thiscall EARSObject::init(void* this) {
    // Call base class constructor or shared initialization
    FUN_006bccd0();

    // Set initial state fields
    *(int*)((char*)this + 0x0c) = 0;   // +0x0c: m_refCount or similar
    *(int*)((char*)this + 0x2c) = 0;   // +0x2c: m_flags or timer

    // If a secondary pointer is non-null, release it via function pointer at +0x1c
    int* ptr = *(int**)((char*)this + 0x10);
    if (ptr != 0) {
        void (*releaseFunc)(void*) = *(void (**)(void*))((char*)this + 0x1c);
        releaseFunc(ptr);
    }

    // Clear pointer fields
    *(int**)((char*)this + 0x10) = 0;  // +0x10: m_targetPointer
    *(int**)((char*)this + 0x18) = 0;  // +0x18: m_anotherPointer
    *(int**)((char*)this + 0x14) = 0;  // +0x14: m_linkPointer
    *(int*)((char*)this + 0x30) = 0;   // +0x30: m_stateFlag

    // Set booleans
    *(bool*)((char*)this + 0x35) = 0;  // +0x35: m_isInitialized
    *(bool*)((char*)this + 0x34) = 1;  // +0x34: m_activeFlag
}