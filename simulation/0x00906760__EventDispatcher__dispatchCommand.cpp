// FUNC_NAME: EventDispatcher::dispatchCommand
void __thiscall EventDispatcher::dispatchCommand(int thisPtr, int *commandIdPtr)
{
    int selectedData;
    undefined local_8;
    char local_4;

    // Check if the stored command ID matches the incoming command ID
    if (*(int *)(thisPtr + 0x2c) == *commandIdPtr) {
        // Choose data source based on state flag and global condition
        if (*(int *)(thisPtr + 0x18) == 0 && *(char *)(DAT_01129908 + 0x18) != '\0') {
            selectedData = *(int *)(thisPtr + 0x1c);
        } else {
            selectedData = *(int *)(thisPtr + 0x24);
        }
        local_8 = 0;
        local_4 = 0;
        // Invoke the associated action with the selected data and a zero parameter
        sendEvent(&selectedData, 0);  // FUN_00408a00
        // Clear the matched command ID
        clearCommandId(thisPtr + 0x2c); // FUN_004086d0
    }
    // No return value
}