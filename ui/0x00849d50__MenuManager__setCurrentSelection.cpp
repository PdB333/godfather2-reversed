// FUNC_NAME: MenuManager::setCurrentSelection
// Function address: 0x00849d50
// Sets the current selection in a UI menu or item selector.
// Stores previous selection and triggers an action if both are non-zero and different.

void __thiscall MenuManager::setCurrentSelection(int newSelection)
{
    int oldSelection = *(int *)(this + 8); // +0x8: current selected item ID/pointer

    if (oldSelection != newSelection)
    {
        if (oldSelection != 0)
        {
            *(int *)(this + 0xc) = oldSelection; // +0xC: store previous selection
        }
        *(int *)(this + 8) = newSelection; // update current selection

        // Debug/log call using a global string (DAT_0112dcf4)
        undefined4 local_c = DAT_0112dcf4;
        undefined4 local_8 = 0;
        undefined1 local_4 = 0;
        FUN_00408a00(&local_c, 0); // likely debug log or console output

        // If both current and previous are valid and different, perform action
        if ((*(int *)(this + 8) != 0) && (*(int *)(this + 0xc) != 0) &&
            (*(int *)(this + 0xc) != *(int *)(this + 8)))
        {
            FUN_006af760(); // some preparation step
            int iVar1 = FUN_00849cf0(*(undefined4 *)(this + 8)); // check if new selection is valid
            if (iVar1 != 0)
            {
                FUN_007e9030(); // apply/execute the selection
            }
        }
    }
    return;
}