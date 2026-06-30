// FUNC_NAME: InputActionManager::processInputEvent
// Function address: 0x0050fdc0
// Role: Processes input events (press/release/other) for a given controller slot and button ID.
// Accesses global input slot array (TLS-based), checks action mapping and state.

void InputActionManager::processInputEvent(unsigned int slotIndex, int* pButtonId)
{
    int* pActionArray;
    InputButtonData* pButtonData;
    int actionIndex;
    int* pActionEntry;
    char buttonState;

    // Access global input slot array from TLS: FS:[0x2c] -> pointer to some structure -> offset 8 points to array of 0x50-byte slots
    // Then add slotIndex * 0x50 + 0x20 (base of button data) + offset from *pButtonId
    pButtonData = (InputButtonData*)(*(int*)(*(int*)(*(int*)(__readfsdword(0x2c) + 8) + 8) + slotIndex * 0x50 + 0x20 + *pButtonId);
    // Note: the double dereference likely goes through a process-local storage object

    pActionArray = (int*) *(int*)(this + 0xac);  // +0xac : pointer to array of action entries (4 bytes each)

    if (pActionArray != 0)
    {
        actionIndex = (unsigned int)*(unsigned short*)(pButtonData + 0x36); // +0x36 : ushort action index
        pActionEntry = (int*)pActionArray[actionIndex]; // each entry is a pointer to an action data object

        if (pActionEntry != 0)
        {
            buttonState = *(char*)(this + 0x5b); // +0x5b : current button state (1=pressed, 2=released, 6=special)

            if (buttonState == 1)
            {
                // Pressed
                if (pActionEntry != 0)
                {
                    // Check a flag at this+0x24 -> offset 0x104
                    if ((*(unsigned char*)(*(int*)(this + 0x24) + 0x104) & 0x10) != 0)
                    {
                        FUN_0051b250(pActionEntry);  // Execute primary action
                        FUN_004f98d0();              // Play feedback/sound
                        return;
                    }
                    FUN_0051b340();  // Execute alternate action
                }
            }
            else if (buttonState == 2)
            {
                // Released
                FUN_004e97b0();  // Handle release
                // Clear the action entry in the array
                *(int*)(pActionArray + actionIndex) = 0;
                return;
            }
            else if (buttonState == 6)
            {
                // Special state (e.g. double-tap or held)
                *(int*)(pButtonData + 0x30) = 0; // Reset some field
                FUN_0050a750();  // Reset action state
                *(int*)(pActionArray + actionIndex) = 0;
                return;
            }
        }
    }
    return;
}