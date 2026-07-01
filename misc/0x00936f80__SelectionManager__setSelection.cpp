// FUNC_NAME: SelectionManager::setSelection
void __thiscall SelectionManager::setSelection(int *this, int newSelection)
{
    // Close any existing selection (debug output)
    DebugPrint("CloseSelection", 0, &G_DEBUG_SELECTION_STATE, 0);
    // Store the new selection ID at offset +0x50
    this[0x14] = newSelection; // +0x50 = offset 0x50 (size 4 per 0x14*4=0x50)
    // Open the new selection (debug output)
    DebugPrint("OpenSelection", 0, &G_DEBUG_SELECTION_STATE, 0);
    // Reset selection state: copy global, zero rest, then call reset function
    int local_c = G_SELECTION_GLOBAL;
    int local_8 = 0;
    char local_4 = 0;
    ResetSelectionState(&local_c, 0);
}