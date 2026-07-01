// FUNC_NAME: RefCountedHandle::~RefCountedHandle

// Destructor for a reference-counted handle (strong reference).
// Releases the owned object and optionally deletes this handle.
// Offset 0x00: vtable pointer (set to base class vtable)
// Offset 0x20: pointer to shared reference-counted object (RefCountedObject)
struct RefCountedObject {
    void **vtable;     // +0x00
    int refCount;      // +0x04
};

undefined4 * __thiscall RefCountedHandle::~RefCountedHandle(undefined4 *this, byte deleteFlag)
{
    int *refCounter;   // Points to refCount of owned object
    RefCountedObject *obj;

    // Release the owned object
    if (this[8] != 0) {
        obj = (RefCountedObject *)this[8];
        refCounter = &obj->refCount;
        *refCounter = *refCounter - 1;

        // If ref count reaches zero, destroy the object via virtual destructor
        if (obj->refCount == 0) {
            // Call the second virtual function (destructor) on the object
            (*(void (**)(void))(obj->vtable[1]))();
        }
        this[8] = 0;   // Clear the owned pointer
    }

    // Reset vtable to base class (base destructor call chain)
    this[0] = &PTR_LAB_00e3729c;

    // Optionally delete this handle if caller requested it
    if ((deleteFlag & 1) != 0) {
        operator delete(this);   // FUN_004eb3d0
    }

    return this;
}