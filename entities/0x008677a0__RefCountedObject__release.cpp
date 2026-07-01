// FUNC_NAME: RefCountedObject::release
void RefCountedObject::release(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
    int *refCountPtr;
    char result;
    int refCount;
    undefined1 local_4[4]; // unused, likely for return value of FUN_00865500
    
    refCount = 0;
    result = FUN_00867690(param_1, param_2, param_3, param_4, param_5, &refCount); // likely getRefCount or similar
    if (result != '\0') {
        refCountPtr = (int *)(refCount + 0x18); // +0x18: reference count field
        *refCountPtr = *refCountPtr + -1; // decrement ref count
        if (*refCountPtr == 0) {
            FUN_00865500(local_4, &refCount); // likely deleteObject or destroy
        }
    }
    return;
}