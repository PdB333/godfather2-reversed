// FUNC_NAME: HashTable::findByQuadID
int __thiscall HashTable::findByQuadID(void* thisPtr, const QuadID* id)
{
    int node;
    int result;
    int current;
    int next;

    // The quad ID is stored as four 32-bit integers (128-bit total)
    // Check if the ID is not the null/sentinel value
    if ((((id->dword0 != 0) || (id->dword1 != 0) || (id->dword2 != 0) || (id->dword3 != 0)) &&
        // Also not the invalid sentinel (-0x45245246 = 0xBABDBDBA, etc.)
        ((id->dword0 != 0xBABDBDBA) || (id->dword1 != 0xBEFBEEEF) ||
         (id->dword2 != 0xEAC15A55) || (id->dword3 != 0x91100911))) &&
        // Check if the hash table root pointer (offset 0x6C in this) is non-null
        (node = *(int*)((char*)thisPtr + 0x6C), node != 0))
    {
        // Walk the linked list (next pointer at offset 0x10 in each node)
        // Each node stores the quad ID at offsets 0x20, 0x24, 0x28, 0x2C
        do {
            current = node;
            if ((*(int*)(current + 0x20) == id->dword0) &&
                (*(int*)(current + 0x24) == id->dword1) &&
                (*(int*)(current + 0x28) == id->dword2) &&
                (*(int*)(current + 0x2C) == id->dword3))
            {
                return current;
            }
            node = *(int*)(current + 0x10);
        } while (node != 0);
    }
    return 0; // Not found
}