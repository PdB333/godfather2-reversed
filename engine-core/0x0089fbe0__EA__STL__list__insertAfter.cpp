// FUNC_NAME: EA::STL::list::insertAfter
// Function address: 0x0089fbe0
// Role: Insert a new node into a doubly linked list after a given position node.
// The node structure (16 bytes) has layout:
//   +0x00: prev (pointer to node)
//   +0x04: next (pointer to node)
//   +0x08: data (stored value – an int pointer)
//   +0x0C: backLink (pointer from data object back to node's data field, used for removal)
// The data object (if non-null) is expected to have at +0x04 a pointer that is updated to point back to the new node's data field (intrusive list pattern).
// param_1 = position node (after which to insert)
// param_2 = pointer to a int value (the data pointer to copy into the new node)

void EA::STL::list::insertAfter(int *positionNode, int **dataPtr)
{
    int **newNode;
    int *dataVal;
    int **nodeDataField;

    // Allocate a new node (size 0x10 = 4 int pointers) using EASTL allocator
    newNode = (int **)FUN_0068ab90(0x10, "EASTL", 0, 0,
                                   "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h",
                                   0xe9);

    nodeDataField = newNode + 2;  // Address of newNode->data (offset +0x08)

    if (nodeDataField != (int **)0x0) {
        dataVal = *dataPtr;
        *nodeDataField = dataVal;                // Set data field of new node
        newNode[3] = (int *)0x0;                  // Clear backLink (offset +0x0C)

        if (dataVal != (int *)0x0) {
            // Copy the existing backLink from the data object (offset +0x04) into newNode->backLink
            newNode[3] = (int *)dataVal[1];       // dataVal[1] is the backLink from the data object
            // Update the data object's backLink to point to the node's data field
            dataVal[1] = (int)nodeDataField;
        }
    }

    // Link the new node into the list after positionNode
    newNode[0] = positionNode;               // newNode->prev = positionNode
    newNode[1] = (int *)positionNode[1];     // newNode->next = positionNode->next

    // Update positionNode->next->prev to point to newNode
    **(int ***)&positionNode[1] = newNode;

    // Update positionNode->next to point to newNode
    positionNode[1] = (int)newNode;

    return;
}