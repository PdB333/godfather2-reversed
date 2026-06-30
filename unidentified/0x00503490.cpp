// FUN_00503490: RefCounted::conditionalRelease

struct RefCountedObject {
    void* vtable;      // +0x00: pointer to virtual function table
    int   refCount;    // +0x04: reference count
};

// Fastcall: param_1 (unused, likely ECX), param_2 (EDX) – a context/flag for conditional release,
// param_3 (stack) – pointer to the ref-counted object.
// Decrements the reference count. If the object's virtual function at vtable+8 returns true,
// the caller receives a non‑null pointer (success); otherwise null.
// If the refcount reaches zero, the object is destroyed via vtable[1].
int* __fastcall conditionalRelease(int unused, int context, RefCountedObject* obj) {
    if (obj == nullptr) {
        return nullptr;
    }

    // Call virtual function "shouldRelease" (vtable offset 0x8)
    typedef bool (__fastcall* ShouldReleaseFunc)(int);
    ShouldReleaseFunc shouldRelease = (ShouldReleaseFunc)((int**)obj->vtable)[2];
    bool releaseCondition = shouldRelease(context);

    // Decrement reference count
    obj->refCount--;

    // If refcount becomes zero, destroy the object via vtable[1]
    if (obj->refCount == 0) {
        typedef void (__fastcall* DestroyFunc)();
        DestroyFunc destroy = (DestroyFunc)((int**)obj->vtable)[1];
        destroy();
    }

    // Return a non‑null pointer if the condition was true, else null
    // (In practice the returned address points to a stack local, but the caller uses it as a boolean.)
    if (releaseCondition) {
        int marker = 0;
        return (int*)&marker;  // non-null "true" indicator
    } else {
        return nullptr;
    }
}