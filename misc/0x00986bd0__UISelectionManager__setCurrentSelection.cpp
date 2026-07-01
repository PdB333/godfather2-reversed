// FUNC_NAME: UISelectionManager::setCurrentSelection

// Function address: 0x00986bd0
// Role: Sets the currently selected UI element. If the new selection differs from the current,
// it closes the previous selection (sending a "CloseSelection" event), clears some internal
// structure, updates the stored selection ID at this+0x54, and then opens the new selection
// (sending an "OpenSelection" event).

void __thiscall UISelectionManager::setCurrentSelection(int newSelection)
{
    int currentSelection = *(int *)(this + 0x54); // +0x54: current selection ID
    
    if (currentSelection != newSelection)
    {
        // Send close event for the old selection
        dispatchUIEvent("CloseSelection", 0, &DAT_00d90fa8, 0);
        
        // Temporary structure used to clear or reset something
        UIStruct tempStruct;
        tempStruct.field0 = DAT_011302b0;
        tempStruct.field4 = 0;
        tempStruct.field8 = 0;
        clearUIStruct(&tempStruct, 0);
        
        // Update the stored selection
        *(int *)(this + 0x54) = newSelection;
        
        // Send open event for the new selection
        dispatchUIEvent("OpenSelection", 0, &DAT_00d90fa8, 0);
    }
}