// FUNC_NAME: RefCountedObject::invokeMethod
// Address: 0x00854be0
// This function increments the reference count of a reference-counted object,
// calls a virtual method on it (at vtable offset 0x2C) using arguments from a
// 4-element array plus an extra parameter, then decrements the reference count.
// If the count reaches zero, the object's destructor (vtable offset 0x04) is invoked.

// Forward declaration of the post-call handler (implemented at 0x00854b50)
void postProcessResult(int result);

struct RefCountedObject {
    void** vtable;      // +0x00
    int      refCount;  // +0x04
};

typedef int ArgArray[4]; // +0x00..0x0C

void FUN_00854be0(ArgArray* pArgs, RefCountedObject* pObj, int extraArg) {
    if (pObj) {
        pObj->refCount++; // increment ref count
    }

    // Call virtual method at vtable offset 0x2C.
    // The method takes the four elements of pArgs, extraArg, and the pObj pointer as arguments.
    // Return value is passed to postProcessResult.
    int result = ((int (*)(int, int, int, int, int, RefCountedObject*))
                  (pObj->vtable[0x2C / 4]))(
        (*pArgs)[0], (*pArgs)[1], (*pArgs)[2], (*pArgs)[3], extraArg, pObj);

    postProcessResult(result);

    // Decrement reference count
    pObj->refCount--;
    if (pObj->refCount == 0) {
        // Call destructor (vtable entry at offset 0x04)
        ((void (*)())(pObj->vtable[0x04 / 4]))();
    }
}