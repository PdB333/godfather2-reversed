// FUNC_NAME: Manager::AttachNode
// Function address: 0x007cb210
// This function appears to set or replace a node in an intrusive singly linked list.
// The 'this' pointer (offset 0x3064) stores the head of the list.
// The node structure (containing a 'next' pointer at offset +4) is located at param2 + 0x48.
// When setting a new node, its 'next' pointer is set to point to the head pointer field itself,
// enabling efficient removal later. FUN_004daf90 is likely a detach/remove function.
void __thiscall Manager::AttachNode(void *node)
{
    // Pointer to the head field in this manager
    int **headPtr = reinterpret_cast<int **>(reinterpret_cast<char *>(this) + 0x3064);
    int *nodePtr; // will hold the actual node structure address

    if (node == 0) {
        nodePtr = 0;
    } else {
        // The actual list node is embedded at offset 0x48 in the passed object
        nodePtr = reinterpret_cast<int *>(reinterpret_cast<char *>(node) + 0x48);
    }

    // Only update if the head is different
    if (*headPtr != nodePtr) {
        // If there was an existing head, detach it (FUN_004daf90 does the removal)
        if (*headPtr != 0) {
            FUN_004daf90(headPtr); // headPtr is the address of the head field; detach the old node
        }

        // Set new head
        *headPtr = nodePtr;

        if (nodePtr != 0) {
            // Save the old head's next pointer into this->0x3068 (maybe for iteration?)
            *(reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x3068)) = *(nodePtr + 1);
            // Point the new node's next pointer back to the head field address
            *(nodePtr + 1) = reinterpret_cast<int>(headPtr);
        }
    }
}