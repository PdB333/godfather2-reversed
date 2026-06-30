// FUNC_NAME: InputManager::updateControllerState
// Address: 0x00534ff0
// Updates global controller state based on connection and player existence flags.
// Globals:
//   g_controllerState (DAT_01219b14): current controller mode (0=no controller, 1=controller no player, 2=controller+player)
//   g_controllerIndex (DAT_01219b21): active controller slot index
//   g_pInputState (DAT_012058e8): pointer to current input state object
//   g_defaultInputState (DAT_01219a70): default input state object
//   g_controllerDataA (array at 0x01219d3c, stride 0x3c): per-slot pointer or state
//   g_controllerDataB (array at 0x01219d40, stride 0x3c): per-slot pointer or state
// Parameters: param_1 = controllerConnected (bool), ESI = playerExists (bool)
void InputManager::updateControllerState(int controllerConnected)
{
    int oldMode;
    int newMode;
    int controllerIndex;
    
    // Store raw parameters into globals (for debugging or deferred handling)
    g_controllerConnected = controllerConnected;       // _DAT_01219b28
    g_playerExists = (int)unaff_ESI;                   // _DAT_01219b24

    // Only update if current input state pointer equals the default input state
    if (g_pInputState == &g_defaultInputState) {
        // Skip when in special modes (3 or 4)
        if ((g_controllerState != 3) && (g_controllerState != 4)) {
            // Compute new desired mode:
            //  0 = no controller connected
            //  1 = controller connected but no player
            //  2 = controller connected with player
            newMode = 0;
            if (unaff_ESI != 0) {
                newMode = (controllerConnected != 0) + 1;
            }
            // If mode actually changed, trigger state transition
            if (g_controllerState != newMode) {
                FUN_00534d70(g_controllerState); // handleLeaveControllerMode
            }
        }
        // Check per-slot cleanup flags (one per controller index)
        controllerIndex = g_controllerIndex;
        if (*(int*)(&g_controllerDataA + controllerIndex * 0x3c) != 0) {
            FUN_006063b0(); // cleanupSlotA
        }
        if (*(int*)(&g_controllerDataB + controllerIndex * 0x3c) != 0) {
            FUN_006063b0(); // cleanupSlotB
        }
    }
}