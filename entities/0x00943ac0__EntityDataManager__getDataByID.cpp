// FUNC_NAME: EntityDataManager::getDataByID
// Function address: 0x00943ac0
// Role: Looks up an entry by ID in an internal array and returns a pointer to data at offset +8 from the entry's data pointer.
// The class likely manages entity data with a mapping from ID to index.
// Offset 0xf0: pointer to an array of 8-byte entries (each entry: [4 bytes unknown, 4 bytes dataPtr]).
// The dataPtr points to a structure; we return dataPtr + 8 (likely a field within that structure).
// If the ID is not found (index == -1), returns a default pointer (possibly null + 8, which is invalid; may be a global default).

int __thiscall EntityDataManager::getDataByID(int thisPtr, int id)
{
    int index;
    
    // Convert ID to an index via a helper function (likely a hash or linear search)
    index = FUN_00941490(&id);  // Note: may actually take id by value; decompiler shows address of stack param
    if (index >= 0) {
        // Access the array at thisPtr+0xf0, each entry is 8 bytes
        // Entry structure: [4 bytes unknown, 4 bytes dataPtr] at offset 4
        // Dereference dataPtr and add 8 to get the desired field
        return *(int *)(*(int *)(thisPtr + 0xf0) + 4 + index * 8) + 8;
    }
    // Fallback: return a default pointer (likely a global or null; here represented as 0+8)
    return 0 + 8;  // iRam00000000 is likely a null pointer constant
}