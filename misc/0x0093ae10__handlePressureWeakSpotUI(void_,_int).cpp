// FUNC_NAME: handlePressureWeakSpotUI(void*, int)
// Function at 0x0093ae10: Handles visibility of pressure/weak spot bonus UI elements based on action code.
// Called with action codes: 0=show weak spot, 2=disable auto-hide pressure, 3=enable auto-hide pressure.
void handlePressureWeakSpotUI(void* pObject, int actionCode) {
    char result;
    // Stack structure for some UI command (0x8 bytes? Actually 12 bytes: data, zero, zero)
    struct {
        int data;
        int zero1;
        int zero2;
    } uiCommand;

    if (actionCode == 0) {
        // Check if weak spot bonus should be shown
        result = FUN_0078af40(); // Possibly CheckShouldShowWeakSpotBonus()
        if (result != 0) {
            // Show weak spot bonus via some UI system
            FUN_005a04a0("ShowWeakSpotBonus", 0, &DAT_00d8a64c, 0);
        }
        // Call processing function on the object (likely resets state)
        FUN_00939ee0(pObject);
        // Setup UI command with global data
        uiCommand.data = DAT_011301e0; // g_pWeakSpotBonusData?
        uiCommand.zero1 = 0;
        uiCommand.zero2 = 0;
        FUN_00408a00(&uiCommand, 0); // Execute command
    } else if (actionCode == 2) {
        // Disable auto-hide pressure string
        FUN_00939ee0(pObject); // Reset object state
        FUN_005a04a0("DisableAutoHidePressureStr", 0, &DAT_00d8a64c, 0);
        uiCommand.data = DAT_011302d0; // g_pDisableAutoHideData?
        uiCommand.zero1 = 0;
        uiCommand.zero2 = 0;
        FUN_00408a00(&uiCommand, 0);
        return; // Explicit return (no further actions)
    } else if (actionCode == 3) {
        // Enable auto-hide pressure string
        FUN_00939ee0(pObject);
        FUN_005a04a0("EnableAutoHidePressureStr", 0, &DAT_00d8a64c, 0);
        // Also hide weak spot bonus
        FUN_005a04a0("HideWeakSpotBonus", 0, &DAT_00d8a64c, 0);
        uiCommand.data = DAT_01130258; // g_pEnableAutoHideData?
        uiCommand.zero1 = 0;
        uiCommand.zero2 = 0;
        FUN_00408a00(&uiCommand, 0);
        return;
    }
    // No explicit return for actionCode==0? Original has fall-through to return.
}