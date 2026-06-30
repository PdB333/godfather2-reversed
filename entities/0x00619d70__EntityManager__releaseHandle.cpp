// FUNC_NAME: EntityManager::releaseHandle
void __thiscall EntityManager::releaseHandle(int this, int* handleStruct)
{
    // Check if the handle's ID matches the expected ID stored at offset 0x18
    if (*handleStruct == *(int*)(this + 0x18))
    {
        // Release the resource associated with the handle's data field (index 2)
        releaseHandleData(handleStruct[2]);
        // Perform global cleanup/notification
        notifyCleanup();
    }
}