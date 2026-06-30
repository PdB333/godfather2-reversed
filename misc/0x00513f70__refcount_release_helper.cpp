// FUNC_NAME: refcount_release_helper
// Function at 0x00513f70: Decrements intrusive reference count on an object,
// conditionally calls destructor based on a vtable check. Used by several release paths.
// Object layout: vtable pointer at +0, reference count (int) at +4
// vtable[1] (offset +4) = destructor (__thiscall void destroy(void))
// vtable[2] (offset +8) = condition check (__thiscall bool canRelease(void* context))

bool releaseRefCountedObject(void* context, void* object) {
    if (object == nullptr) {
        return false;
    }

    // vtable at first 4 bytes of object
    void** vtable = *(void***)object;
    // Destructor at vtable[1]
    auto destroy = (void(__thiscall*)(void*))vtable[1];
    // Condition function at vtable[2], takes context parameter
    auto canRelease = (bool(__thiscall*)(void*, void*))vtable[2];

    bool shouldDelete = canRelease(object, context);

    int* refCount = (int*)((char*)object + 4);
    (*refCount)--;

    if (*refCount == 0) {
        destroy(object);
        // After destroy, object is invalid; don't touch further
    }

    // Return true if the object was actually deleted (or "ready" flag)
    return shouldDelete;
}