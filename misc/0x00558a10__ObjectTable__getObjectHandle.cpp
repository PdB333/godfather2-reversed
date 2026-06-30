// FUNC_NAME: ObjectTable::getObjectHandle
undefined4 __thiscall ObjectTable::getObjectHandle(int this, int id)
{
    int relativeIndex;
    
    // Get base array and its length from stored pointer at offset +4
    // The structure at this+4 is likely a pointer to a header with base address and count
    int* header = *(int**)(this + 4);
    int arrayBase = header[0]; // base address of the object array
    int arrayLength = header[1]; // number of valid slots
    
    relativeIndex = id - arrayLength;
    
    if (relativeIndex < 0)
    {
        // Direct index into the array (id is within range)
        // Each entry at id * 0x70 bytes from arrayBase, and within that entry
        // there is a pointer at offset 0x40 that points to additional data
        int* entryPtr = *(int**)(arrayBase + 0x40 + id * 0x70);
        return *(undefined4*)(entryPtr + 0x10);
    }
    
    // If a backup table exists (at this+0x1c), use it for IDs beyond the base array length
    if (*(int*)(this + 0x1c) != 0)
    {
        int* backupHeader = *(int**)(this + 0x1c);
        int* backupArray = *(int**)(backupHeader + 0x10);
        int* outerArray = *(int**)(backupArray + 0x30);
        int* entryPtr = *(int**)(*outerArray + 0x40 + relativeIndex * 0x70);
        return *(undefined4*)(entryPtr + 0x14);
    }
    
    // Fallback to a global array (likely a singleton or static table)
    int* globalArray = *(int**)(0x30); // piRam00000030 – presumed global pointer
    int* entryPtr = *(int**)(globalArray + 0x40 + relativeIndex * 0x70);
    return *(undefined4*)(entryPtr + 0x14);
}