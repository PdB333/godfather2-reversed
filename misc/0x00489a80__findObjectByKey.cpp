// FUNC_NAME: findObjectByKey
int __fastcall findObjectByKey(void* unused, void* container, int** outPtr, int key)
{
    // Container layout:
    // +0x10: pointer to an array of pointers (each pointing to an object whose first 4 bytes is a key)
    // +0x14: number of elements in that array

    int found = 1; // assume outPtr already points to the correct object

    // If outPtr is not currently valid (null or wrong key), we need to search
    if (*outPtr == NULL || **outPtr != key)
    {
        uint32_t count = *(uint32_t*)((char*)container + 0x14);
        if (count != 0)
        {
            uintptr_t** ppArray = *(uintptr_t***)((char*)container + 0x10);
            for (uint32_t i = 0; i < count; i++)
            {
                // Compare the first integer of the pointed object with the key
                if (*(int*)(ppArray[i]) == key)
                {
                    *outPtr = (int*)ppArray[i];
                    return 1; // found
                }
            }
        }
        found = 0; // not found
    }
    return found;
}