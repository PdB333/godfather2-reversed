// FUNC_NAME: CleanupList::~CleanupList
// Function at 0x0054a460: Destructor for a class that manages a list of cleanup callbacks and a reference-counted shared object.
// Layout: this+0x0 = vtable, this+0x4 = pointer to ref-counted shared object, this+0x8 = pointer to callback list structure

struct CallbackListData {
    // +0x0: unknown padding?
    int field_0;
    // +0x4: unknown
    int field_4;
    // +0x8: array of function pointers to call (each takes int arg)
    code** callbacks;
    // +0xc: count of callbacks
    int callbackCount;
};

struct RefCountObject {
    // +0x0: vtable pointer
    code** vtable;
    // +0x4: short (maybe flags)
    short flags;
    // +0x6: reference count
    short refCount;
};

// Global vtables referenced (addresses from code)
extern void* PTR_FUN_00e39c38;   // "destructor vtable" (first set)
extern void* PTR_LAB_00e39c34;   // "base vtable" (restored at end)

void __thiscall CleanupList::~CleanupList(CleanupList* this)
{
    // Set vtable to the destructor's vtable
    this->vtable = &PTR_FUN_00e39c38;

    // Get the callback list
    CallbackListData* callbacks = this->callbackList;
    if (callbacks->callbackCount > 0) {
        // Iterate and call each callback with argument 0 (cleanup)
        for (int i = 0; i < callbacks->callbackCount; i++) {
            code* func = callbacks->callbacks[i];
            func(0);
        }
    }

    // Handle the reference-counted shared object
    RefCountObject* refObj = this->refCountedObj;
    if (refObj->flags != 0) {
        // Decrement the secondary reference count at +0x6
        refObj->refCount--;
        if (refObj->refCount == 0) {
            // If it reached zero, call the vtable function with argument 1 (likely delete or release)
            code* releaseFunc = refObj->vtable[0];
            releaseFunc(1);
        }
    }

    // Restore vtable to base vtable (likely for base class destructor)
    this->vtable = &PTR_LAB_00e39c34;
}