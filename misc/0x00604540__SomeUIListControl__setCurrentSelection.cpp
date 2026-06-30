// FUNC_NAME: SomeUIListControl::setCurrentSelection
void __thiscall SomeUIListControl::setCurrentSelection(uint newIndex)
{
    // Pointer to internal data manager at +0x20
    int* dataManager = *(int**)(this + 0x20);
    // +0xA8: total number of items in the list
    uint itemCount = *(uint*)(dataManager + 0xA8);
    
    // Only process if new index is valid and different from current (+0x40)
    if (newIndex < itemCount && *(uint*)(this + 0x40) != newIndex)
    {
        // Update current selection index
        *(uint*)(this + 0x40) = newIndex;
        
        // Always call the same refresh/update function
        // (redundant condition from decompilation)
        if (newIndex < itemCount)
            FUN_004d3d90(); // updateSelectionVisuals
        else
            FUN_004d3d90(); // updateSelectionVisuals
    }
}