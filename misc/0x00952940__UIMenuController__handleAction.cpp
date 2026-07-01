// FUNC_NAME: UIMenuController::handleAction
// Address: 0x00952940
// Handles input actions for a UI menu. Compares action ID with current state,
// invokes virtual method at vtable+0x2c for matching action, or sends MoveUp/MoveDown commands.

int __thiscall UIMenuController::handleAction(int* thisPtr, int actionId)
{
    int currentAction = FUN_00466840(); // Get current active action/state

    if (actionId == currentAction) {
        // Invoke virtual method (likely onSelect or onActivate)
        (*(void (__thiscall**)(int*))(*(int*)thisPtr + 0x2c))(thisPtr);
        return 0;
    }

    const char* commandName;
    if (actionId == 8) {
        commandName = "MoveUp";
    }
    else if (actionId == 9) {
        commandName = "MoveDown";
    }
    else {
        return 0;
    }

    // Send command via global event system
    FUN_005a04a0(commandName, 0, &DAT_00d8bea0, 0);
    thisPtr[0x16] = 0; // Reset some member (e.g., selection index) // +0x58 (since 0x16 * 4 = 0x58)
    return 0;
}