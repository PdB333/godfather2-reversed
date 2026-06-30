// FUN_004afca0: ObjectFactory::createObject
// Role: Creates an object of type 0x2001 using the factory instance at `this`.
int ObjectFactory::createObject(ObjectFactory* thisPtr)
{
    int result;               // iVar1
    int outObject[2];         // local_8 [2] - output pointer/status pair

    result = 0;
    // Check if factory is valid and internal pointer at +0x10 (likely allocator or vtable) is non-null
    // Note: The decompiled condition was `*(char *)(param_1 + 0x10) + param_1 != 0`, which is interpreted as a check on a pointer.
    if (thisPtr != 0 && *(void**)((char*)thisPtr + 0x10) != 0) {
        allocateInternal(outObject, 0x2001);  // FUN_004af8c0, likely allocate from pool or create with ID
        result = 0;
        if (outObject[0] != 0) {
            result = outObject[0];  // return the newly allocated object pointer
        }
    }
    return result;
}