// FUNC_NAME: unknownClass::attachToListHead
// Address: 0x006ba790
// Inserts a node (this) at the head of a doubly linked list stored inside a container object.
// The container's head pointer is at offset 0x48 (and perhaps tail at 0x4C).
// Node has next at +0x00, prev at +0x04.

int* __thiscall attachToListHead(int* node, int* container) {
    // If container is non-null, compute pointer to its list head field (container + 0x48)
    int* headField;
    if (container != 0) {
        headField = (int*)((char*)container + 0x48);
    } else {
        headField = 0;
    }

    // Check if node is already at the head (its next pointer matches the head field address)
    if (node[0] != (int)headField) {
        // If node was in a list (next non-null), remove it via helper
        if (node[0] != 0) {
            FUN_004daf90(node);  // removal function
        }

        // Set node's next to the address of the head field
        node[0] = (int)headField;

        // If list head exists, link node into the list
        if (headField != 0) {
            // node->prev = headField[1]  (likely the tail pointer at offset 0x4C)
            node[1] = headField[1];
            // headField[1] becomes this node (i.e., tail pointer now points to node)
            headField[1] = (int)node;
        }
    }

    return node;
}