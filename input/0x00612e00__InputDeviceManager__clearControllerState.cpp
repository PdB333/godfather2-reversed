// FUNC_NAME: InputDeviceManager::clearControllerState
// Function at 0x00612e00: Clears a controller's state, disconnects device, and resets global flags.
// Called on shutdown, device removal, or player disconnection.
void __fastcall InputDeviceManager::clearControllerState(int this) {
    uint deviceId; // +0xa0: controller device ID (or connection handle)
    
    // If there is an active device
    if (*(uint *)(this + 0xa0) != 0) {
        deviceId = *(uint *)(this + 0xa0) & 0xff;
        
        // Check if the device slot (index from +0x14) is marked as XInput (or similar)
        // The global array at g_deviceFlags is indexed by slot*16
        // g_deviceFlags[slot * 16] != 0 means XInput device
        if (g_deviceFlags[*(int *)(this + 0x14) * 0x10] != '\0') {
            deviceId += 0x10; // offset for XInput devices to a separate state bank
        }
        
        // Release the device (e.g., close handle, free resources)
        releaseInputDevice(); // FUN_00618d40
        // Clear the state array entry for this device
        g_deviceStateArray[deviceId] = 0;
    }
    
    // Reset global controller flags
    g_bControllerEnabled = 0;   // DAT_012058f0
    g_bControllerActive = 0;    // DAT_012058e8
}