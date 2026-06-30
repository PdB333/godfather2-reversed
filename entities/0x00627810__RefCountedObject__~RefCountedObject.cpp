//FUNC_NAME: RefCountedObject::~RefCountedObject

void __thiscall RefCountedObject::~RefCountedObject(void* this)
{
    int* refCountPtr;

    // Global cleanup routine (likely decrements global reference or performs engine-level cleanup)
    FUN_006382a0();

    // Base class destructor or member cleanup
    FUN_00627500(this);

    // Call a function pointer stored in a global table (possibly vtable or destructor chain)
    (*DAT_012059e0)();

    // If this object is valid, decrement a reference count stored in an internal structure
    if (this != 0) {
        // this+0x10 points to an internal structure (e.g., a shared resource manager)
        // That structure has a reference count at offset 0x24
        refCountPtr = (int*)(*(int*)((char*)this + 0x10) + 0x24);
        *refCountPtr = *refCountPtr - 0x58; // Decrement by 0x58 (likely a counter or allocation size)
    }
    return;
}