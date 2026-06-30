// FUNC_NAME: InputDeviceManager::processControllerState
void __fastcall InputDeviceManager::processControllerState(int this)
{
    char deviceState;   // byte at this+0x14
    uint controllerIndex; // loop variable
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    // Offset 0x14 likely stores the current controller index or a special value
    if (*(char *)(this + 0x14) == '\x13') {
        // Special case: 0x13 (19) probably means "poll all 16 controllers"
        controllerIndex = 0;
        do {
            // Check if controller 'controllerIndex' is connected (0x1000 = buffer size, 2 = flag)
            char connectionResult = checkControllerConnection(controllerIndex, 0x1000, 2);
            if (connectionResult != '\0') {
                // Initialize or process the connected controller
                initializeController(controllerIndex);
                break;
            }
            controllerIndex = controllerIndex + 1;
        } while (controllerIndex < 0x10);
    }
    else {
        // Single controller specified by the byte at +0x14
        char connectionResult = checkControllerConnection(*(char *)(this + 0x14), 0x1000, 2);
        if (connectionResult != '\0') {
            // Set status at +0x10 to 2 (e.g., "connected and active")
            *(undefined4 *)(this + 0x10) = 2;
        }
    }

    // If status is 2 (active), perform update operations
    if (*(int *)(this + 0x10) == 2) {
        // Reset controller state buffer (likely clear input data)
        resetControllerState(*(undefined1 *)(this + 0x14), 0x1000);
        // Global debug flag check
        if (g_bDebugEnabled != 0) {
            // Some debug visualization call (e.g., draw axis helper)
            debugDrawControllerHelper(0, 0, 0);
        }
        // Build a local 3D point from global data (likely debug coordinate offset)
        local_c = g_debugTextOffsetX; // DAT_01129a98
        local_8 = 0;
        local_4 = 0;
        // Draw debug text for controller
        debugDrawText(&local_c, 0);
    }
    return;
}