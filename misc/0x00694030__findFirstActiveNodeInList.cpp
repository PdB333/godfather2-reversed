// FUNC_NAME: findFirstActiveNodeInList
// Address: 0x00694030
// Traverses a singly-linked list of nodes until it finds a node with a non-zero byte at offset +0x29.
// Node structure: +0x00: pointer to next node, +0x29: active flag (char).
// The function discards the found node pointer; it is purely a traversal side-effect.
// Called from 0x00695ac0.

void findFirstActiveNodeInList(int** listHeadPtr)
{
    // Dereference to get the current node pointer
    uint8_t* currentNode = (uint8_t*)*listHeadPtr;
    // Check the active flag at offset 0x29
    char activeFlag = *(char*)(currentNode + 0x29);

    // Loop until we find a node with a non-zero flag
    while (activeFlag == '\0') {
        // Move to the next node (link at offset 0x00)
        currentNode = *(uint8_t**)(currentNode);
        activeFlag = *(char*)(currentNode + 0x29);
    }
    // Node found; no further action (function returns void)
}