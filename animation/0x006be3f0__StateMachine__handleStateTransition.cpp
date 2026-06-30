// FUNC_NAME: StateMachine::handleStateTransition
void __thiscall StateMachine::handleStateTransition(int thisPtr, int newStateID)
{
    int selectedData;
    // Compare new state ID with current state ID at offset 0x54
    if (newStateID == *(int *)(thisPtr + 0x54)) {
        // Use state-specific data at +0x60
        selectedData = *(int *)(thisPtr + 0x60);
    } else {
        // Use default data at +0x68
        selectedData = *(int *)(thisPtr + 0x68);
    }
    // Call internal reset/initialize function on the selected data
    FUN_00408a00(&selectedData, 0); // Likely zeros out data or sets default values
    return;
}