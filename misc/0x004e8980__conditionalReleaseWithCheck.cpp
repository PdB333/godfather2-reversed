// FUNC_NAME: conditionalReleaseWithCheck
// Address: 0x004e8980
// Purpose: Decrements refcount of a reference‑counted object.
//          If a virtual check (vtable[2]) succeeds, returns a pointer to a local (non‑null sentinel);
//          otherwise returns null. The object is released (vtable[1]) when refcount reaches zero.
// Note: param_1 (ecx) is unused – possibly a left‑over __fastcall calling convention artifact.
struct RefCountedObject {
    void** vtable;  // +0x00
    int refCount;   // +0x04
};

void* __fastcall conditionalReleaseWithCheck(int unused_ecx, int identifier, RefCountedObject* pObj) {
    int local_success_indicator = 0;  // local variable used only to obtain a non‑null address
    if (pObj != nullptr) {
        // vtable[2] is a virtual method that takes the identifier and returns a bool
        bool matched = reinterpret_cast<bool (*)(int)>(pObj->vtable[2])(identifier);
        if (matched) {
            pObj->refCount--;
            if (pObj->refCount == 0) {
                reinterpret_cast<void (*)()>(pObj->vtable[1])(); // release / destructor
            }
            return &local_success_indicator; // non‑null (stack address)
        }
        // if the check failed, still decrement and potentially release
        pObj->refCount--;
        if (pObj->refCount == 0) {
            reinterpret_cast<void (*)()>(pObj->vtable[1])();
        }
    }
    return nullptr;
}