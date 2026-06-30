// FUNC_NAME: setControllerVibration
void setControllerVibration(float vibrationLevel)
{
    // Store the vibration level globally
    g_vibrationLevel = vibrationLevel;

    // Check if the input system is in a valid state and the current controller slot has a device
    if ((g_inputStatePointer == &g_validStateMarker) && (g_controllerArray[g_currentControllerIndex].devicePtr != nullptr))
    {
        // Prepare a zeroed buffer (likely for vibration parameters)
        uint8_t vibrationBuffer[4] = {0, 0, 0, 0}; // local_20
        // Call the function to apply vibration to the specific controller
        applyVibrationToController(g_inputManager, g_controllerArray[g_currentControllerIndex].devicePtr, vibrationBuffer);
    }
}