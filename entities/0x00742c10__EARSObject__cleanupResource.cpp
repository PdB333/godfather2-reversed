// FUNC_NAME: EARSObject::cleanupResource
void __thiscall EARSObject::cleanupResource(int thisPtr)
{
    int type = *(int*)(thisPtr + 0x54); // +0x54: resource type identifier (0 = none, 0x48 = persistent)
    int* dataPtr = *(int**)(thisPtr + 0x50); // +0x50: pointer to resource data

    // Only deallocate if type is non-zero and not the persistent marker (0x48)
    if (type != 0 && type != 0x48)
    {
        MemoryManager::deallocate(dataPtr); // Calls EARS memory deallocation at 0x00878dc0
    }
}