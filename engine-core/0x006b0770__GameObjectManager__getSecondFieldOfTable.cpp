// FUNC_NAME: GameObjectManager::getSecondFieldOfTable
// Function at 0x006b0770: Accessor for the second DWORD of an 8-byte structure in a table pointed by this+0x34.
int __thiscall GameObjectManager::getSecondFieldOfTable(void* this, int index)
{
    // Pointer to table of 8-byte structures stored at this+0x34
    int* table = *(int**)((char*)this + 0x34);
    // Return the second 4-byte field (offset +4) of the indexed entry
    return *(int*)((char*)table + 4 + index * 8);
}