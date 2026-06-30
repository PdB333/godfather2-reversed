// FUNC_NAME: releaseRefCountedObject
// Function at 0x004F76D0: Decrements the reference count of a ref-counted object and conditionally deletes it.
// Parameters:
//   ecx: ignored (may be 'this' for a wrapper class)
//   edx (param2): argument passed to the "canRelease" virtual function (e.g., a context or flag)
//   stack (param3): pointer to a RefCountedObject structure (vtable at +0, refCount at +4)
// Returns 1 if the "canRelease" check succeeded, 0 otherwise.
// The refcount is always decremented, and if it reaches zero, the object's destructor (vtable+4) is called.

struct RefCountedObjectVTable {
    void (*releaseCheck)(void* obj, int context);  // offset 0x0? Actually might be other functions.
    void (*destructor)(void* obj);                // offset 0x4
    int  (*canRelease)(void* obj, int context);   // offset 0x8 (returns bool)
};

struct RefCountedObject {
    RefCountedObjectVTable* vtable; // +0x0
    int refCount;                   // +0x4
};

// __fastcall: ecx unknown/unused, edx = context, stack = obj pointer
int __fastcall releaseRefCountedObject(int ecx, int context, void* obj) {
    if (obj == nullptr) {
        return 0;
    }

    RefCountedObject* refObj = reinterpret_cast<RefCountedObject*>(obj);
    RefCountedObjectVTable* vtable = refObj->vtable;

    // Check if this object can be released (e.g., is still alive)
    if (vtable->canRelease(refObj, context)) {
        // Decrement refcount
        refObj->refCount--;
        if (refObj->refCount == 0) {
            // Call destructor
            vtable->destructor(refObj);
        }
        return 1; // Success
    } else {
        // Even if can't release, still decrement refcount (possibly a forced release?)
        refObj->refCount--;
        if (refObj->refCount == 0) {
            vtable->destructor(refObj);
        }
        return 0; // Failure (condition not met)
    }
}