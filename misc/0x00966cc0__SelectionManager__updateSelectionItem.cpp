// FUNC_NAME: SelectionManager::updateSelectionItem

void SelectionManager::updateSelectionItem(void)
{
    int managerPtr = g_selectionManager;          // DAT_01129930
    int savedState = *(int *)(managerPtr + 0xc4); // +0xc4: current state/mode

    uint currentAnalog = getAnalogInput();         // FUN_0095c9f0
    uint deadzone = getDeadzoneThreshold();        // FUN_0095ca80
    uint storedAnalog = *(uint *)(managerPtr + 0x1dc); // +0x1dc: stored analog value

    // Apply deadzone: if current analog is within the deadzone range, skip update
    if (currentAnalog <= storedAnalog) {
        if (storedAnalog <= deadzone) {
            goto LAB_00966cf7;
        }
    } else {
        // currentAnalog > storedAnalog -> clamp? Or just proceed
    }

    // Update stored analog with current analog
    *(uint *)(managerPtr + 0x1dc) = currentAnalog;

LAB_00966cf7:
    // Set state to 3 for UI interaction
    *(int *)(managerPtr + 0xc4) = 3;

    // Notify UI/input system about the selection change
    setUIAction(3, *(int *)(managerPtr + 200), *(int *)(managerPtr + 0xcc)); // FUN_0095fbc0

    // Debug/log "UpdateSelectItem"
    debugPrint("UpdateSelectItem", 0, &DAT_00d8cdec, 0); // FUN_005a04a0

    // Restore original state
    *(int *)(managerPtr + 0xc4) = savedState;

    // Clean up UI context after processing
    clearUIAction(3); // FUN_0095e7d0
}