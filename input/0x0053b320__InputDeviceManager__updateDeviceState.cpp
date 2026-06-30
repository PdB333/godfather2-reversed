//FUNC_NAME: InputDeviceManager::updateDeviceState
// Function address: 0x0053b320
// Updates input device state for a given device index, applying axis values to the active player's data.

// Global arrays (defined elsewhere):
// g_deviceStateArray: array of 0x1000 device state structures, each 0x38 bytes.
// g_playerDataArray: array of pointers to player data structures (size 0x3c per entry), indexed by g_activePlayerIndex.
// g_activePlayerIndex: current active player index (byte).
// g_someGlobal: pointer used as first argument to setPlayerInputAxis.

void InputDeviceManager::updateDeviceState(int deviceIndex)
{
    // Check if the active player has a valid data pointer
    int* playerDataPtr = *(int**)((uint)&g_playerDataArray + (uint)g_activePlayerIndex * 0x3c);
    if (playerDataPtr != nullptr)
    {
        // Get device state structure from the global array (0x38 bytes per entry)
        DeviceState* deviceState = nullptr;
        if (deviceIndex < 0x1000)
        {
            deviceState = &g_deviceStateArray[deviceIndex];
        }
        else
        {
            deviceState = nullptr; // Invalid index, should not happen
        }

        // Read axis values from the device state (ushort at offsets +2 and +4)
        float axisX = (float)*(ushort*)((uint)deviceState + 2);
        float axisY = (float)*(ushort*)((uint)deviceState + 4);

        // Call function to set the input axis for the player
        // Arguments: global pointer, player data pointer, address of axisX (first float)
        setPlayerInputAxis(g_someGlobal, playerDataPtr, &axisX);
    }

    // Check another player data pointer (different array) and call update function if valid
    int* otherPlayerDataPtr = *(int**)((uint)&g_otherPlayerDataArray + (uint)g_activePlayerIndex * 0x3c);
    if (otherPlayerDataPtr != nullptr)
    {
        updatePlayerSomething();
    }
}