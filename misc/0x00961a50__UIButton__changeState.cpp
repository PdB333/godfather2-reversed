// FUNC_NAME: UIButton::changeState
// Address: 0x00961a50
// This function handles state changes for a UI button, dispatching rollover/rollout events.
// The button has a selection state at offset +0x60.
// State 4 is special: it represents the "selected" or "active" state (e.g., a pressed button).

void __thiscall UIButton::changeState(int thisPtr, int newState)
{
    int currentState;
    int tempState;

    currentState = *(int *)(thisPtr + 0x60);  // +0x60: m_selectionState
    if (newState != currentState) {
        // When leaving the selected state (4), roll out the entire button.
        // Otherwise, roll out the selection indicator.
        if (currentState == 4) {
            postNotification("RollOutButton", 0, &DAT_00d8d668, 1, &DAT_00e36da0);
        } else {
            packIntToString(&tempState, &DAT_00e3266c, currentState);
            postNotification("RollOutSelection", 0, &DAT_00d8d668, 1, &tempState);
        }

        // When entering the selected state (4), roll over the entire button.
        // Otherwise, roll over the selection indicator.
        if (newState == 4) {
            postNotification("RollOverButton", 0, &DAT_00d8d668, 1, &DAT_00e36da0);
            *(int *)(thisPtr + 0x60) = 4;
            return;
        }

        packIntToString(&tempState, &DAT_00e3266c, newState);
        postNotification("RollOverSelection", 0, &DAT_00d8d668, 1, &tempState);
        *(int *)(thisPtr + 0x60) = newState;
    }
    return;
}