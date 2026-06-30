// FUNC_NAME: ObjectArray::findObjectByType

int __thiscall ObjectArray::findObjectByType(uint typeId) {
    // this structure:
    // +0x00: int** array (pointer to array of entries; each entry is 8 bytes, first 4 bytes are a pointer)
    // +0x04: int count (number of entries)
    int count = *(int*)((char*)this + 4);
    int* arrayBase = *(int**)this;
    
    for (int i = 0; i < count; i++) {
        int entryPtr = arrayBase[i * 2]; // stride of 8 bytes (2 ints)
        if (entryPtr != 0 && entryPtr != 0x48) {
            // check if byte at offset 0x165 from this pointer matches typeId
            if (*(byte*)(entryPtr + 0x165) == (byte)typeId) {
                // return the base pointer (subtract 0x48 to get parent object)
                return entryPtr - 0x48;
            }
        }
    }
    return 0;
}