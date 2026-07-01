// FUNC_NAME: ObjectManager::tryProcessByHash
// Address: 0x008ece40
// Role: Look up an object by a 4-int hash key, verify list consistency, and process an action if conditions are met.

int __thiscall ObjectManager::tryProcessByHash(int *thisPtr, int *key4, int param3, int param4)
{
    int listHead;          // local_8 - pointer to list head node
    int currentNode;       // local_4 - pointer to current node in iteration
    int listVersion;       // iVar1 from this+0x10
    bool found;            // result from hashLookup
    int hash;              // computed hash from key

    // Compute a hash from the 4-int key using multiply-by-33 (like djb2 but without initial seed)
    // Equivalent to (((key[0]*33 + key[1])*33 + key[2])*33 + key[3])
    hash = key4[0] * 0x21 + key4[1];
    hash = hash * 0x21 + key4[2];
    hash = hash * 0x21 + key4[3];

    // Look up whether this hash is valid (returns nonzero if found)
    found = hashLookup(hash); // FUN_004059b0

    if (found) {
        // Get a list node pointer and the iterator starting point using the computed hash
        getListHeadAndCurrent(&listHead, &hash); // FUN_008ec8c0 (note: hash is passed by reference, may be modified? No, it's not used after this)
        
        listVersion = *(int *)(thisPtr + 0x10);

        // Assert that if the list head is non-null, it must point to the object's built-in list head (this+0xC)
        if ((listHead != 0) && (listHead != thisPtr + 0xC)) {
            debugAssert(); // FUN_00b97aea
        }

        // Check if current node (from iterator) is different from the stored version (listVersion)
        if (currentNode != listVersion) {
            // More consistency checks
            if (listHead == 0) {
                debugAssert();
            }
            if (currentNode == *(int *)(listHead + 4)) {
                debugAssert();
            }

            // Check if the current node's type/state field is 2
            if (*(int *)(currentNode + 0x18) == 2) {
                // Ensure current node is not the next of head (again - double check)
                if (currentNode == *(int *)(listHead + 4)) {
                    debugAssert();
                }
                // Call the processing function with the supplied parameters
                processAction(param3, param4); // FUN_008eb6b0
                return 1; // success
            }
        }
    }
    return 0; // not processed
}