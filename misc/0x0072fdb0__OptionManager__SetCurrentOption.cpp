// FUNC_NAME: OptionManager::SetCurrentOption
// Address: 0x0072fdb0
// Role: Sets the currently highlighted/selected UI option. Updates linked list pointers.
// Parameters: param_1 - pointer to UI option object (0 means deselect). 
// The option object has a linked list header at offset 0x48 (prev/next?).

void OptionManager::SetCurrentOption(int optionPtr)
{
    OptionManager* manager = GetOptionManagerSingleton(); // FUN_007f41e0
    if (manager == nullptr)
        return;

    // Offset 0x68: pointer to current option (head of list?)
    int** currentOptionPtr = (int**)((uint8_t*)manager + 0x68);
    
    // Adjust option pointer: if optionPtr is 0, keep 0; otherwise add 0x48 to point to the option's list node.
    int adjustedOption = (optionPtr == 0) ? 0 : optionPtr + 0x48;

    if (*currentOptionPtr != adjustedOption)
    {
        // Remove old current option from list if present
        if (*currentOptionPtr != 0)
        {
            RemoveFromList(currentOptionPtr); // FUN_004daf90 - unlinks the node
        }

        // Set new current option
        *currentOptionPtr = adjustedOption;

        if (adjustedOption != 0)
        {
            // Link the new node: copy manager's "previous" pointer (or something) from node+4, 
            // and set node's pointer back to manager's list head.
            // Offset 0x6c in manager: probably "currentOptionPrev" or something similar.
            *(int**)((uint8_t*)manager + 0x6c) = *(int**)(adjustedOption + 4); // copy old prev?
            *(int**)(adjustedOption + 4) = currentOptionPtr; // set node's back link to manager's head
        }

        // Post a message (0x200) to notify UI of change
        PostMessage(0x200); // FUN_004abc20
    }
}