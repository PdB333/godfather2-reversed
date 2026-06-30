// FUNC_NAME: RefCountedHandle::initialize
// Address: 0x005fba60
// Role: Initializes a ref-counted handle object that attaches to a source object and optionally stores a resource ID.

// Based on decompilation from Ghidra.
// This function appears to be a constructor-like initializer for a class that holds a reference to another object
// (with its own vtable) and possibly attaches a resource handle. The class has fields at offsets 0x10 and 0x14.

// Forward declarations for external functions (addresses noted)
int FUN_004265d0(int param1, void* param2); // Converts a handle or index using a source pointer
void FUN_005fc100(void* source, int value); // Registers or attaches the value to the source

// The class being initialized (partial layout)
class RefCountedHandle {
public:
    // Vtable pointer at offset 0x00 (set by caller)
    // Unknown fields at offsets 0x04..0x0F? (not used here)
    void* m_pSource; // +0x10: pointer to source object (with vtable)
    int m_nResourceId; // +0x14: resource ID or handle (0 if none)

    // Initializer - mimics __thiscall; returns this pointer
    RefCountedHandle* __thiscall initialize(void* source, int resourceId);
};

RefCountedHandle* __thiscall RefCountedHandle::initialize(void* source, int resourceId) {
    void* pSource = source;
    void** vtable = *(void***)pSource; // assume source has vtable

    // Call vtable+8 (first time) - likely an addRef or init on the source, passing the source itself?
    ((void (*)(void*))((int)vtable[2]))(pSource); // vtable[2] = offset 8 (0x8)

    int result;
    if (resourceId == 0) {
        result = 0;
    } else {
        result = FUN_004265d0(resourceId, pSource); // convert resourceId using source context
    }

    FUN_005fc100(pSource, result); // associate the result with source

    this->m_pSource = source; // offset 0x10

    // Call vtable+8 again (second time) - but no argument this time. Possibly a different method?
    // The decompiler shows same offset but with no argument. We replicate exactly.
    ((void (*)())((int)vtable[2]))();

    if (resourceId != 0) {
        // Convert again and store at offset 0x14
        int id = FUN_004265d0(resourceId, this->m_pSource);
        this->m_nResourceId = id; // offset 0x14
        // Call vtable+4 (setData?): takes resourceId and zero
        ((void (*)(void*, int, int))((int)vtable[1]))(pSource, resourceId, 0);
        // Call vtable+12 (finalize/release?): no args
        ((void (*)())())((int)vtable[3])();
        return this;
    } else {
        this->m_nResourceId = 0; // offset 0x14
        // Call vtable+12 (finalize/release?): no args
        ((void (*)())())((int)vtable[3])();
        return this;
    }
}