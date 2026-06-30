// FUNC_NAME: ResourceManager::getOrLoadPointer
int* __fastcall ResourceManager::getOrLoadPointer(ResourceManager* thisPtr)
{
    int* objectPtr;
    int outData; // unused output buffer

    // Check if the resource is already loaded (flag at offset 0x1c)
    if (*(char*)((int)thisPtr + 0x1c) != '\0') {
        // Resource already loaded – get the vtable pointer and call a method
        objectPtr = (int*)*((int*)thisPtr); // dereference first field as a pointer
        outData = 0;
        // Call vtable+0x2c with (this, 0, 0, &outData, 0x10)
        // This appears to load or validate the resource (size 0x10 bytes into outData)
        (**(code**)(*objectPtr + 0x2c))(objectPtr, 0, 0, &outData, 0x10);
        return objectPtr;
    }
    // Resource not loaded – set a loading flag and return the stored pointer
    *(char*)((int)thisPtr + 0x1d) = 1; // mark as loading/in-use
    return (int*)*((int*)thisPtr + 4); // return pointer at offset 0x10
}