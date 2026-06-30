// FUNC_NAME: updateScreenElementValue
// Address: 0x00534ef0
// Role: Updates a UI element value based on controller analog input and calls related processing.
// Reads from global input device state table (0x38 bytes per entry, up to 0x1000 entries)
// Then uses current screen ID to index into two arrays (0x3c stride) for element pointers.
// Called from FUN_005334b0 (likely UI update loop)

void updateScreenElementValue(void)
{
    uint controllerIndex; // unaff_ESI - passed in ESI register, index into input device table
    float analogX;
    float analogY;
    void* elementPtr;
    void* secondElementPtr;

    // Check if the element for this screen exists (using global screen ID)
    elementPtr = *(void**)(&g_screenElementsArray + (uint)g_currentScreenId * 0x3c);
    if (elementPtr != (void*)0x0) {
        // Get pointer to input device state for this controller
        undefined1* deviceState;
        if (controllerIndex < 0x1000) {
            deviceState = &g_inputDeviceStates + controllerIndex * 0x38;
        } else {
            deviceState = (undefined1*)0x0;
        }
        // Read analog stick values: X at offset +2, Y at offset +4 (both ushorts)
        analogX = (float)*(ushort*)(deviceState + 2);
        analogY = (float)*(ushort*)(deviceState + 4);
        // Call function to set element value (likely position or analog value)
        FUN_0060ac80(g_uiManager, elementPtr, &analogX);
    }
    // Check second element for this screen
    secondElementPtr = *(void**)(&g_secondScreenElementsArray + (uint)g_currentScreenId * 0x3c);
    if (secondElementPtr != (void*)0x0) {
        // Additional processing for second element
        FUN_006063b0();
    }
}