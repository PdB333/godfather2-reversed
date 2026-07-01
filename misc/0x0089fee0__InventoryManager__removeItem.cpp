// FUNC_NAME: InventoryManager::removeItem
void __thiscall InventoryManager::removeItem(int thisPtr, int itemId) {
    // Linked list head at this+0x34, each node is a structure with next(0), prev(4), and a pointer to item field(8)
    int* listHead = (int*)(thisPtr + 0x34);
    int* currentNode = (int*)*listHead;
    
    // Traverse the list
    if (currentNode != listHead) {
        while (true) {
            // Extract item identifier: if node->field8 is non-zero, subtract 0x1c to get the object base
            int itemBase = (currentNode[2] != 0) ? (currentNode[2] - 0x1c) : 0;
            if (itemId == itemBase) {
                break; // Found the node matching the ID
            }
            currentNode = (int*)*currentNode;
            if (currentNode == listHead) {
                return; // Not found
            }
        }
        
        // Check if this item is the currently selected one (stored at this+0xb4)
        int* currentSelectionPtr = (int*)(thisPtr + 0xb4);
        int selectedBase = (currentSelectionPtr[0] != 0) ? (currentSelectionPtr[0] - 0x1c) : 0;
        if (selectedBase == itemId && currentSelectionPtr[0] != 0) {
            // Deallocate or release the selection pointer
            FUN_004daf90(currentSelectionPtr);
            *currentSelectionPtr = 0; // Clear selection
        }
        
        // Remove the node from the linked list (FUN_0089f970 definitely removes)
        // currentNode[2] is the field pointer (offset within the object)
        int* itemFieldPtr = &currentNode[2];
        FUN_0089f970(itemFieldPtr);
        
        // If the object base is valid, call its virtual destructor with arg 1
        if (itemFieldPtr[0] != 0) {
            int* objectBase = (int*)(itemFieldPtr[0] - 0x1c);
            (*(void (__thiscall**)(int, int))(*objectBase))(objectBase, 1);
        }
    }
}