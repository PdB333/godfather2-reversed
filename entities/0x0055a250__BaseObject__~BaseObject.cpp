// FUNC_NAME: BaseObject::~BaseObject
class BaseObject {
public:
    // +0x00: Primary vtable pointer (for this class)
    // +0x04: Secondary vtable pointer (e.g., for interface or base class)
    void* m_vtable1;
    void* m_vtable2;
    // +0x34 (0xd * 4): Pointer to a child object or internal component
    void* m_childObject;
    
    virtual ~BaseObject() = 0; // purecall
};

// Destructor for BaseObject
BaseObject* __thiscall BaseObject::~BaseObject(BaseObject* this, byte flags) {
    // Step 1: Set vtable to sub-destructor to allow proper virtual dispatch during cleanup
    *(void**)this = (void*)&PTR_FUN_00e3a038;  // sub-destructor vtable
    this->m_vtable2 = (void*)&PTR_LAB_00e3a054;

    // If the child object pointer is non-null, perform cleanup
    if (this->m_childObject != 0) {
        cleanupChildObject(this); // FUN_009f1b20 - presumably deletes or resets child
        globalCleanupFunction();  // FUN_009f01a0 - global state reset (no arguments)
    }

    // Step 2: Switch vtable to base destructor (purecall) to prevent further virtual calls
    this->m_vtable2 = (void*)&PTR_LAB_00dc3dd4;
    *(void**)this = (void*)&PTR___purecall_00e3924c;

    // If the 'delete' flag (bit 0) is set, free the memory
    if ((flags & 1) != 0) {
        deallocateMemory(this); // FUN_009c8eb0 - operator delete
    }
    return this;
}

// Note: Function addresses for cleanup calls:
//   cleanupChildObject: 0x009f1b20
//   globalCleanupFunction: 0x009f01a0
//   deallocateMemory: 0x009c8eb0
// Vtable symbols:
//   PTR_FUN_00e3a038, PTR_LAB_00e3a054, PTR_LAB_00dc3dd4, PTR___purecall_00e3924c