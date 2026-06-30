// FUNC_NAME: ObjectManager::resolveHandle
void* __fastcall ObjectManager::resolveHandle(void* thisPtr, int handle)
{
    // Local variables: dummy byte for status, output pointer
    char statusDummy; // +0x00
    void** outObjectPtr; // +0x04

    // Look up object from handle, returns an internal structure pointer on success
    int internalStruct = FUN_005f0560(handle, &statusDummy, &outObjectPtr);
    if (internalStruct != 0)
    {
        // Offset +0x18 holds the actual object pointer
        return *(void**)(internalStruct + 0x18);
    }
    return 0;
}