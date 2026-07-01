// FUNC_NAME: setListNode
// Function address: 0x0079d780
// Role: Sets a linked list node pointer at offset 0x30a4, inserting a new node (at object+0x48) into a doubly linked list.
// The node structure at offset 0x48 has a "prev" pointer at +4 (relative to node start) that points to the location holding the pointer to this node.
// The function removes the old node (if any) via FUN_004daf90, then inserts the new node.

void __thiscall setListNode(int thisPtr, int objectWithNode)
{
    int *nodePtrPtr = (int *)(thisPtr + 0x30a4); // pointer to the head node pointer
    int newNodePtr;

    if (objectWithNode == 0) {
        newNodePtr = 0;
    } else {
        newNodePtr = objectWithNode + 0x48; // node is embedded at offset 0x48 in the object
    }

    if (*nodePtrPtr != newNodePtr) {
        if (*nodePtrPtr != 0) {
            FUN_004daf90(nodePtrPtr); // remove old node from list
        }
        *nodePtrPtr = newNodePtr; // set head to new node
        if (newNodePtr != 0) {
            // Save the old "prev" pointer of the new node (which pointed to its previous location)
            *(int *)(thisPtr + 0x30a8) = *(int *)(newNodePtr + 4);
            // Set the new node's "prev" to point to the head pointer location
            *(int **)(newNodePtr + 4) = nodePtrPtr;
        }
    }
    return;
}