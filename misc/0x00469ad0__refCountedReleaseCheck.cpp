// FUNC_NAME: refCountedReleaseCheck
bool __fastcall refCountedReleaseCheck(uint unused1, void* arg2, int* refCountPtr)
{
    if (refCountPtr == nullptr)
    {
        return false;
    }

    // vtable layout: [0] = unknown, [1] = destructor, [2] = check function
    RefCountVTable* vtbl = reinterpret_cast<RefCountVTable*>(*refCountPtr);
    bool checkResult = vtbl->checkFunc(arg2);
    
    // Decrement reference count stored at offset 4 from refCountPtr
    int* count = refCountPtr + 1;
    (*count)--;
    if (*count == 0)
    {
        vtbl->destructor();
    }

    return checkResult;
}