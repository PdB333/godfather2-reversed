// FUNC_NAME: ListManager::attachNode
void __thiscall ListManager::attachNode(int this, int nodeContainer)
{
    // this+0xf4: pointer to current head node (or null)
    // this+0xf8: pointer to previous head's "prev" pointer (or null)
    int *headPtr = (int *)(this + 0xf4);
    int newNode;
    
    if (nodeContainer == 0) {
        newNode = 0;
    } else {
        // Node is embedded at offset 0x48 within the container
        newNode = nodeContainer + 0x48;
    }
    
    if (*headPtr != newNode) {
        // Remove old head if present
        if (*headPtr != 0) {
            FUN_004daf90(headPtr); // likely unlink or release
        }
        *headPtr = newNode;
        if (newNode != 0) {
            // Save the previous "prev" pointer (nodeContainer+4) into this+0xf8
            *(int *)(this + 0xf8) = *(int *)(nodeContainer + 4);
            // Update the node's "prev" pointer to point to the head pointer
            *(int **)(nodeContainer + 4) = headPtr;
        }
    }
}