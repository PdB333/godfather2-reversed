// FUNC_NAME: RefCountedPtr::constructor
// Function at 0x005f9900: Constructor for a reference-counted pointer wrapper.
// Takes an object pointer (objectPtr) and an optional reference count delta (refCountDelta).
// Stores the object pointer at this+0x10 and the reference count at this+0x14.
// Calls virtual functions on the object to manage reference counting.

int RefCountedPtr::constructor(int thisPtr, int *objectPtr, int refCountDelta)
{
    int *obj = objectPtr;
    // Call virtual function at vtable+8 (likely init or retain)
    (**(code **)(*objectPtr + 8))(objectPtr);
    
    int refCount;
    if (refCountDelta == 0) {
        refCount = 0;
    } else {
        refCount = FUN_004265d0(refCountDelta, obj); // Possibly duplicate or copy
    }
    
    FUN_005fa100(obj, refCount); // Possibly assign or release old reference
    
    *(int **)(thisPtr + 0x10) = objectPtr; // +0x10: stored object pointer
    (**(code **)(*objectPtr + 8))(); // Call same virtual again? (likely with objectPtr)
    
    if (refCountDelta != 0) {
        refCount = FUN_004265d0(refCountDelta, *(int *)(thisPtr + 0x10));
        *(int *)(thisPtr + 0x14) = refCount; // +0x14: stored reference count
        (**(code **)(*objectPtr + 4))(refCountDelta, 0); // vtable+4: addRef or similar
        (**(code **)(*objectPtr + 0xc))(); // vtable+0xc: release or finalize
        return thisPtr;
    }
    
    *(int *)(thisPtr + 0x14) = 0; // +0x14: zero reference count
    (**(code **)(*objectPtr + 0xc))(); // vtable+0xc: release or finalize
    return thisPtr;
}