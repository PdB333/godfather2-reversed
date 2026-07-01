// FUNC_NAME: EntityDataManager::findEntityByGUID
// Function: 0x0082d0c0
// Searches an array of entities (kept as a pointer array at this+0x8, count at this+0xC)
// for one whose four DWORD fields at offsets 0x1C,0x20,0x24,0x28 match the key.
// Returns the entity pointer if found, else nullptr.

int __thiscall EntityDataManager::findEntityByGUID(int thisPtr, int *key)
{
    uint i;
    int entityPtr;
    int *entryArray;

    // count at this+0xC
    if (*(uint *)(thisPtr + 0xC) == 0)
    {
        return 0;
    }

    entryArray = *(int **)(thisPtr + 0x8);   // pointer to array of int*
    i = 0;
    do
    {
        entityPtr = *entryArray;              // dereference to get entity pointer
        // compare four DWORD fields at offsets 0x1C,0x20,0x24,0x28
        if (*(int *)(entityPtr + 0x1C) == key[0] &&
            *(int *)(entityPtr + 0x20) == key[1] &&
            *(int *)(entityPtr + 0x24) == key[2] &&
            *(int *)(entityPtr + 0x28) == key[3])
        {
            return entityPtr;
        }
        i++;
        entryArray++;
    } while (i < *(uint *)(thisPtr + 0xC));

    return 0;
}