// FUNC_ADDRESS: 0x0049f570
// ROLE: Handles controller state change detection and triggers disconnect/reconnect actions
// Class: ControllerManager (hypothetical)
// Method: handleConnectionStateChange

void ControllerManager::handleConnectionStateChange(ControllerState* pControllerState)
{
    // +0x0b2: byte containing bit 0 indicating previous connection state
    bool wasConnected = (pControllerState->fields[0x0b2] & 1) != 0;

    // Check current connection state for the manager (e.g., global controller flags)
    bool currentConnected = (this->controllerFlags & 0x2) != 0; // +0x0ac bit 1

    // Possibly checks hardware state / updates global flag
    bool hardwareState = FUN_0049d050();

    if (currentConnected)
    {
        if (hardwareState == false)
        {
            if (wasConnected)
            {
                // Controller just disconnected – play disconnect sound
                FUN_0042d2c0(*(int*)(DAT_012233a8 + 4), *(int*)(pControllerState + 0x0a0));
            }
        }
        else if (wasConnected == false)
        {
            // Controller just reconnected – reset state
            FUN_0049feb0();
            // Pass some value from the hardware check to complete reconnection
            FUN_0049ef30(extraout_ECX); // extraout_ECX likely returned by FUN_0049d050
            return;
        }
    }
}