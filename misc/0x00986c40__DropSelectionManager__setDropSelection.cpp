// FUNC_NAME: DropSelectionManager::setDropSelection
void __thiscall DropSelectionManager::setDropSelection(int newSelection) {
    // +0x5c: currentDropSelection
    if (*(int*)(this + 0x5c) != newSelection) {
        // Close the previous drop selection
        dispatchEvent("CloseDropSelection", 0, &DAT_00d90fa8, 0);
        *(int*)(this + 0x5c) = newSelection;

        // Initialize a new drop selection event
        DropSelectionEvent event;
        event.someGlobal = DAT_011302b0;
        event.param2 = 0;
        event.param3 = 0;
        initializeDropSelectionEvent(&event, 0);
    }
    // Open the new drop selection
    dispatchEvent("OpenDropSelection", 0, &DAT_00d90fa8, 0);
}