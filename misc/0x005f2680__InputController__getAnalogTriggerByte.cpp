// FUNC_NAME: InputController::getAnalogTriggerByte
short InputController::getAnalogTriggerByte(void)
{
    // this is in EAX
    float floatVal;
    short scaledVal;
    int *deviceData; // pointer to device data structure

    // Default return value: 0
    scaledVal = 0;

    // Check that this pointer is valid and that the device data pointer is not null
    if ((this != (InputController *)0x0) &&
        (deviceData = *this, deviceData != (int *)0x0) &&
        // Check bit 4 of flags at offset +7 (likely a "connected" or "active" flag)
        ((*(byte *)(deviceData + 7) & 4) == 0))
    {
        // Retrieve a child object via handle at offset +0x18 (e.g., a trigger axis component)
        int *childObj = FUN_005dc670(*(undefined4 *)(deviceData + 0x18)); // likely getComponentByID

        if ((childObj != (int *)0x0) &&
            // Read float value at offset +0x280 (e.g., analog trigger position, 0.0 to 1.0)
            (floatVal = *(float *)(childObj + 0x280),
             // Check if within global thresholds (DAT_00e2b05c = min, DAT_00e2b1a4 = max)
             DAT_00e2b05c <= floatVal && floatVal <= DAT_00e2b1a4))
        {
            // Scale to 0-127 range using global scale factor (_DAT_00e44670)
            scaledVal = (short)(int)(floatVal * _DAT_00e44670);
            if (scaledVal < 1) {
                return 0;
            }
            // Clamp to max byte value (127)
            if (scaledVal < 0x7f) {
                return scaledVal;
            }
            scaledVal = 0x7f;
        }
    }
    return scaledVal;
}