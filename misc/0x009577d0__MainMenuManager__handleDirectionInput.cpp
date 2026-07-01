// FUNC_NAME: MainMenuManager::handleDirectionInput
void __thiscall MainMenuManager::handleDirectionInput(int direction)
{
    int currentIndex = *(int *)(this + 0x6c); // +0x6c: currently selected menu item index
    FUN_00957060(currentIndex); // unhighlight or deselect current item
    FUN_009574f0((currentIndex + 6 + direction) % 6); // highlight new item with wrap-around (6 items)
    const char* directionStr;
    if (direction < 0)
        directionStr = "right";
    else
        directionStr = "left";
    // Log menu navigation event
    FUN_005a04a0("UpdateMainMenu", 0, &DAT_00d8c174, 1, directionStr);

    // Register two consecutive state callbacks at offset +0x14 (likely a state machine or renderer)
    FUN_005c0d50(this + 0x14, &LAB_005bfc10, 0);
    FUN_005c0d30();
    FUN_005c0d50(this + 0x14, &LAB_005bfbe0, 0);

    // Build and send a data packet (likely update UI state)
    struct {
        int field0; // +0x00: presumably color or ID
        int field4; // +0x04: padding/flags
        char field8; // +0x08: flags
    } data;
    data.field0 = DAT_01130418;
    data.field4 = 0;
    data.field8 = 0;
    FUN_00408a00(&data, 0);
}