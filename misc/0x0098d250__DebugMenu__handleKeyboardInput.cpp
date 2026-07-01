// FUNC_NAME: DebugMenu::handleKeyboardInput
void __fastcall DebugMenu::handleKeyboardInput(int this)
{
    SHORT keyState;
    int currentItem;
    undefined1 *dataPtr;
    undefined4 *itemArray;
    int *iterator;
    undefined4 *foundItem;
    
    // Check if there are items in the list (difference between end and start pointers)
    if ((*(int *)(this + 0x234) - *(int *)(this + 0x230) & 0xfffffffcU) == 0) {
        return;
    }
    
    // If no selected item index (this+0x120 is 0)
    if (*(int *)(this + 0x120) == 0) {
        itemArray = *(undefined4 **)(this + 0x230);
        if (itemArray == *(undefined4 **)(this + 0x234)) {
            return;
        }
        while( true ) {
            currentItem = FUN_005bec00();  // Get some ID or hash
            foundItem = (undefined4 *)*itemArray;
            if (foundItem[0x10] == currentItem) break;  // Compare item ID
            itemArray = itemArray + 1;
            if (itemArray == *(undefined4 **)(this + 0x234)) {
                return;
            }
        }
    }
    else {
        // If only 1 item (4 bytes difference), return
        if ((*(int *)(this + 0x234) - *(int *)(this + 0x230) & 0xfffffffcU) == 4) {
            return;
        }
        
        iterator = *(int **)(this + 0x230);
        if (iterator == *(int **)(this + 0x234)) {
            return;
        }
        
        // Find item matching selected index (offset +0x30 in item data)
        while (*(int *)(*iterator + 0x30) != *(int *)(this + 0x120)) {
            iterator = iterator + 1;
            if (iterator == *(int **)(this + 0x234)) {
                return;
            }
        }
        
        // Handle shift/up/down navigation
        keyState = GetKeyState(0x10);  // VK_SHIFT
        if (keyState < 0) {
            // Shift pressed: move up (previous item)
            if (iterator == *(int **)(this + 0x230)) {
                iterator = *(int **)(this + 0x234);
            }
            iterator = iterator + -1;
        }
        else {
            // No shift: move down (next item)
            iterator = iterator + 1;
            if (iterator == *(int **)(this + 0x234)) {
                iterator = *(int **)(this + 0x230);
            }
        }
        foundItem = (undefined4 *)*iterator;
    }
    
    // Get string pointer from found item
    dataPtr = (undefined1 *)*foundItem;
    if (dataPtr == (undefined1 *)0x0) {
        dataPtr = &DAT_0120546e;  // Default string if null
    }
    FUN_0098d080(dataPtr, foundItem + 8);  // Call display function with string and some data
    return;
}