// FUN_00446130: HashTable::findNode
// 0x00446130 - Hash table lookup using a 128-bit key (4 ints). 
// Returns a pointer to associated data (via getNodeData) or 0 if not found.

int HashTable::findNode(int *key, uint flags) const
{
    // Compute hash of the key. FUN_004209c0 likely returns a uint hash from the 4-int key.
    uint hash = hashKey(key);  // FUN_004209c0

    // Hash table: array of head pointers at +0x70, capacity at +0x74.
    int headPtr = *(int *)(*(int *)(this + 0x70) + (hash % *(uint *)(this + 0x74)) * 4);

    int node = headPtr;
    while (node != 0)
    {
        // Retrieve pointer to key stored in the node. FUN_0043ab10 returns a pointer to the 4-int key.
        int *nodeKey = getNodeKey(node);  // FUN_0043ab10

        // Compare all 4 ints of the key
        if (nodeKey[0] == key[0] && nodeKey[1] == key[1] && nodeKey[2] == key[2] && nodeKey[3] == key[3])
        {
            break; // found
        }
        node = *(int *)(node + 0x18); // next node in chain
    }

    if (node == 0)
    {
        return 0;
    }

    // Extract some bits from flags (shift right 13, mask with 0xFFFFFF01) and pass the node's stored value at offset +0x08.
    // FUN_00446340 retrieves the actual data from the node.
    int storedValue = *(int *)(node + 8);
    int result = getNodeData(node, storedValue, (flags >> 0xD) & 0xFFFFFF01); // FUN_00446340

    return result;
}