// FUNC_NAME: GlobalStorage::getFloatAtIndex
float __fastcall getFloatAtIndex(int obj)
{
    // Get TLS (Thread-Local Storage) pointer from FS segment offset 0x2C
    // This yields a pointer to the TLS array (first element of the slot table)
    int* tlsArray = *(__readfsdword(0x2C));
    // Slot index 2 (offset +8) holds a pointer to a global manager structure
    int* managerBase = *(int**)(tlsArray + 2); // +0x08: second TLS slot
    // Within the manager, a float array starts at offset 0x78
    float* floatArray = (float*)((char*)managerBase + 0x78);
    // The index into the float array is stored at offset 0x18 in the input object
    int index = *(int*)((char*)obj + 0x18);
    return floatArray[index];
}