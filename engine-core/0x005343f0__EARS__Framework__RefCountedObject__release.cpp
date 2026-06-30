// FUNC_NAME: EARS::Framework::RefCountedObject::release
void EARS::Framework::RefCountedObject::release(void)
{
    // this in esi
    if (this != nullptr) {
        // Call virtual function at vtable+8 (likely second virtual method, maybe getRefCountManager)
        RefCountManager* refMgr = (this->vtable[2])(); // offset 8
        // Access thread-local storage: per-thread data at FS:0x2C
        // Usually points to a per-thread context or list manager
        int* perThreadData = *(int**)(__readfsdword(0x2C) + 0x0); // actually reads pointer at FS:[0x2C] then dereferences
        int* pPerThreadList = *perThreadData; // actually perThreadData is an int*, then we dereference
        // pPerThreadList points to a global list head (maybe free list)
        // Check a flag in a sub-object (offset +0x10 from this[4] i.e., offset 16)
        // Flag is at offset from this[4] + *(pPerThreadList+8)
        // This is an obfuscated way to read a per-class flag for memory management
        if ((*(uint*)(this->field_16 /* unaff_ESI[4] */ + *(int*)(pPerThreadList + 8)) & 0x10000000) != 0) {
            // If flag is set, decrement a reference count stored in a sub-object
            if (this->field_4 /* unaff_ESI[1] */ + 0x10 != 0) {
                short* refCount = (short*)(this->field_4 + 0x10 + 0x3e + *(short*)((int)this + 0xe) * 0x24);
                *refCount = *refCount - 1;
            }
        }
        // Decrement another counter in the ref manager
        refMgr->counter_0x14 = refMgr->counter_0x14 - 1; // possibly total ref count
        // Check another flag
        if ((*(uint*)(this->field_16 + *(int*)(pPerThreadList + 8)) & 0x80000000) == 0) {
            // If flag not set, call virtual function at vtable+4 (first virtual method) – likely a destructor or deallocation
            (this->vtable[1])(); // offset 4
            return;
        }
        // Else, insert this into a linked list (likely a free list or reuse list)
        this->field_8 /* unaff_ESI[2] */ = refMgr->field_0x1c; // previous head
        refMgr->field_0x1c = this; // new head
    }
}