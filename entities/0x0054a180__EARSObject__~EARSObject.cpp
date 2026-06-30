// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x0054a180
// Role: Destructor for EARSObject (base class with reference-counted sub-object and cleanup function array)

void __thiscall EARSObject::~EARSObject(EARSObject* thisObj)
{
    int index;
    void** cleanupFuncArray;
    int cleanupCount;
    short* refCountPtr;
    short* refCountDecPtr;

    // Set vtable to destructor-specific vtable (ensures correct virtual dispatch during destruction)
    thisObj->vtable = &PTR_FUN_00e39c30;

    // Iterate over an array of cleanup function pointers stored at thisObj->cleanupArray
    // The array is at offset +0x8 from the structure pointed to by thisObj->cleanupData (offset +0x8 from this)
    cleanupCount = *(int*)(thisObj->cleanupData + 0xc);
    if (cleanupCount > 0) {
        cleanupFuncArray = (void**)(*(int*)(thisObj->cleanupData + 0x8));
        for (index = 0; index < cleanupCount; index++) {
            // Call each cleanup function with argument 0 (likely "release" or "destroy" sub-objects)
            ((void (*)(int))cleanupFuncArray[index])(0);
        }
    }

    // Handle reference-counted sub-object at thisObj->refCountedSubObj (offset +0x4 from this)
    refCountPtr = (short*)(thisObj->refCountedSubObj + 4);  // +0x4: reference count flag
    if (*refCountPtr != 0) {
        refCountDecPtr = (short*)(thisObj->refCountedSubObj + 6);  // +0x6: decrement counter
        (*refCountDecPtr)--;
        if (*refCountDecPtr == 0) {
            // Call the release function (first vtable entry of sub-object) with argument 1 (delete)
            ((void (*)(int))(*((void**)thisObj->refCountedSubObj)))(1);
        }
    }

    // Set vtable to base class vtable (final vtable after destruction)
    thisObj->vtable = &PTR_LAB_00e39c34;
}