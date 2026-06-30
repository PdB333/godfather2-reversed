// FUNC_NAME: SystemUpdate (global function at 0x0067c050)
// Role: Called during main game loop. Initializes a subsystem, then checks for an active object (e.g., player or controller).
// If found, processes it and updates its UI representation; otherwise, processes with a null/zero argument.

void SystemUpdate(void)
{
    int activeObject;

    // Initialize subsystem (e.g., frame state, input devices)
    InitializeSubsystem();

    // Retrieve an active object pointer/handle. Non-zero indicates something to process.
    activeObject = GetActiveObjectHandle();

    if (activeObject != 0) {
        // Process the active object (e.g., player, vehicle, UI element)
        ProcessObject(activeObject);
        // Update associated UI or HUD component
        UpdateUIComponent(activeObject);
        return;
    }

    // No active object – call processor with a null/zero argument (likely handles cleanup or idle state)
    ProcessObject(0);
    return;
}