// FUNC_NAME: RefCounted::releaseWithCheck
undefined1* __fastcall RefCounted::releaseWithCheck(undefined4 this_unused, undefined4 checkParam, RefCounted* refCountedObj) {
    // this_unused is ignored (likely a dummy or part of calling convention)
    // checkParam is passed to the virtual check function at vtable+8
    // refCountedObj points to a refcounted object: [vtablePtr, refCount]
    // vtable+4 = destructor, vtable+8 = check virtual function returning bool (char)
    // Returns a pointer to a dummy boolean (stack) if check true, else null.
    // The pointer value is used as a truthy indicator of successful conditional release.

    undefined4 local_successFlag = 0;

    if (refCountedObj != nullptr) {
        // Ask the object if it is allowed to release given the check parameter
        bool canRelease = (*(char (__thiscall**)(int, undefined4))(*(int*)refCountedObj + 8))(refCountedObj, checkParam) != 0;
        
        // Always decrement the reference count (at offset +4)
        int* refCount = &refCountedObj->refCount; // +0x04
        *refCount -= 1;
        
        // If refcount reached zero, call destructor via vtable+4
        if (*refCount == 0) {
            (*(void (__thiscall**)(int))(*(int*)refCountedObj + 4))(refCountedObj);
        }
        
        // If the check passed, return a non-null pointer (truthy)
        if (canRelease) {
            return (undefined1*)&local_successFlag;
        }
    }
    // Return null if object was null or check failed
    return (undefined1*)0;
}