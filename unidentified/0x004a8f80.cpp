// FUN_004a8f80: HashTable::findNode
int __fastcall HashTable::findNode(int *hashTable, int key)
{
    // Magic constants indicating uninitialized/invalid table
    const int kSig0 = -0x45245246;  // 0xBADDBDBA? (EA signature)
    const int kSig1 = -0x41104111;  // 0xBEEFBFEF
    const int kSig2 = -0x153EA5AB; // 0xEAC15A55
    const int kSig3 = -0x6EEFF6EF; // 0x91100911

    // If the header matches the "empty" pattern, return null
    if (hashTable[0] == kSig0 && hashTable[1] == kSig1 && hashTable[2] == kSig2 && hashTable[3] == kSig3)
    {
        return 0;
    }

    // Start traversal from the first node in the bucket (current = 0 gets head)
    int node = FUN_00445ff0(hashTable, 0);
    while (node != 0)
    {
        // Key stored at offset 0x18 in each node
        if (*(int *)(node + 0x18) == hashTable[4])
        {
            break;
        }
        node = FUN_00445ff0(hashTable, node);
    }
    return node;
}