// FUNC_NAME: MainMenuController::updateMenu
void __thiscall MainMenuController::updateMenu(int thisPtr)
{
    // Check if something at +0x48 is non-zero (possibly a flag for active state?)
    if (*(char *)(thisPtr + 0x48) == '\0') {
        // No active state, clear value at +0x6C (possibly timer or animation id)
        *(int *)(thisPtr + 0x6C) = 0;
    } else {
        // Call functions to handle active state (e.g., update animation, transition)
        FUN_00957060(*(int *)(thisPtr + 0x6C));  // Likely animation update
        FUN_009574f0(0);                          // Possibly reset something
        // Notify Lua to update main menu visuals
        LuaCall("UpdateMainMenu", 0, &DAT_00d8c174, 1, &DAT_00d8c32c);
    }

    // Clear byte at +0x51 (maybe a "selected" or "hover" flag)
    *(char *)(thisPtr + 0x51) = '\0';

    // Deactivate button "1" (character constant 0x31)
    char button1[] = { 0x31, 0 };
    LuaCall("DeactivateButton", 0, &DAT_00d8c174, 1, button1);

    // Decrement integer at +0x78 if positive (cooldown or timer)
    if (*(int *)(thisPtr + 0x78) > 0) {
        *(int *)(thisPtr + 0x78) -= 1;
    }

    // Clear byte at +0x7C (maybe another timer flag)
    *(char *)(thisPtr + 0x7C) = '\0';

    // Activate button "0" (character constant 0x30)
    char button0[] = { 0x30, 0 };
    LuaCall("ActivateButton", 0, &DAT_00d8c174, 1, button0);

    // Conditionally activate/deactivate another button based on byte at +0x50
    if (*(char *)(thisPtr + 0x50) == '\0') {
        LuaCall("ActivateButton", 0, &DAT_00d8c174, 1, PTR_DAT_00e5743c); // PTR likely a string like "2"
        return;
    }
    LuaCall("DeactivateButton", 0, &DAT_00d8c174, 1, PTR_DAT_00e5743c);
}