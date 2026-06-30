// FUN_0045c190: InputManager::checkControllerAxesIdle
bool checkControllerAxesIdle(uint32_t* axes)
{
    // Axes points to an array of 4 raw axis values (e.g., left stick X/Y, right stick X/Y, or trigger)
    // Constants from global data
    uint32_t axisMask = DAT_00e44680;       // Mask to extract meaningful bits (e.g., 0xFFFF)
    float deadzoneThreshold = DAT_00e44598; // Deadzone threshold as float
    uint32_t centerOffset = DAT_00e2b1a4;   // Offset subtracted only from axis[3] (e.g., trigger center)

    // Check each axis after masking; the fourth axis has a center offset subtracted before masking
    if (((float)(axes[0] & axisMask) < deadzoneThreshold) &&
        ((float)(axes[1] & axisMask) < deadzoneThreshold) &&
        ((float)(axes[2] & axisMask) < deadzoneThreshold) &&
        ((float)((axes[3] - centerOffset) & axisMask) < deadzoneThreshold))
    {
        return true; // All axes are within deadzone (idle)
    }
    return false;
}