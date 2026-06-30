// FUNC_NAME: RefCountHelper::safeCheckAndRelease

#include <cstddef>

// Represents a reference-counted object with a virtual table.
struct RefCountedObject {
    void** vtable; // +0x00
    int refCount;  // +0x04
};

// Checks object validity, decrements reference count, and returns a sentinel or null.
// __fastcall: ECX (unused), EDX = context, stack = obj pointer.
void* __fastcall safeCheckAndRelease(void* /*unused*/, int context, RefCountedObject* obj) {
    int sentinel = 0; // stack variable for non-null sentinel

    if (obj != nullptr) {
        // Virtual function at vtable[2] (offset 8) checks validity with given context.
        // Returns nonzero if valid.
        bool isValid = reinterpret_cast<bool (__thiscall*)(RefCountedObject*, int)>(obj->vtable[2])(obj, context);

        obj->refCount--;
        if (obj->refCount == 0) {
            // Virtual function at vtable[1] (offset 4) destroys the object.
            reinterpret_cast<void (__thiscall*)(RefCountedObject*)>(obj->vtable[1])(obj);
        }

        if (isValid) {
            return &sentinel; // Non-null sentinel indicating success
        }
    }
    return nullptr;
}