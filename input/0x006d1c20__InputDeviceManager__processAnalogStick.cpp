// FUNC_NAME: InputDeviceManager::processAnalogStick
void __thiscall InputDeviceManager::processAnalogStick(int thisObj, float* outX, float* outY, int slotIndex, float deltaTime)
{
    *outX = 0.0f;
    *outY = 0.0f;

    // Get controller object pointer from slot array (base + slotIndex*4)
    int* controllerPtr = *(int**)(*(int*)(g_controllerArrayBase + 4) + slotIndex * 4);
    if (controllerPtr == nullptr || controllerPtr == (int*)0x1f30) // sentinel for disconnected
    {
        return;
    }

    // Check if controller is active (bit 20 of field at offset 0x15c)
    if (((uint)controllerPtr[0x15c] >> 0x14) & 1)
    {
        return;
    }

    // Get device interface from vtable (virtual function at offset 8)
    int deviceId = (*(int(__thiscall**)(int*))(*controllerPtr + 8))();

    // Get raw input state pointer
    int rawStickPtr = FUN_00410540(deviceId);
    if (rawStickPtr == 0)
    {
        return;
    }

    bool invertY = FUN_00410d80(); // check if Y axis should be inverted

    float rawX = *(float*)(rawStickPtr + 8);
    float rawY = *(float*)(rawStickPtr + 0xC);

    if (!invertY)
    {
        // Apply deadzone to raw values
        if ((float)((uint)rawX & kDeadZoneMask) <= kDeadZoneThreshold)
            rawX = 0.0f;
        if ((float)((uint)rawY & kDeadZoneMask) <= kDeadZoneThreshold)
            rawY = 0.0f;

        // Clamp and apply power curve (cube for X, square for Y)
        float clampedX = clamp(rawX, kMinStickValue, kMaxStickValue);
        float clampedY = clamp(rawY, kMinStickValue, kMaxStickValue);
        *outX = clampedX * clampedX * clampedX;  // cubic response
        *outY = clampedY * clampedY;              // quadratic response
    }
    else
    {
        // Inverted: apply sensitivity scaling
        float sensitivityScale = kInvertSensitivity / deltaTime;
        *outX = rawX * sensitivityScale;
        *outY = rawY * sensitivityScale;
    }

    // Apply global inversion flags
    if (g_invertX)
    {
        *outX = kMaxStickValue - *outX;
    }
    if (g_invertY)
    {
        *outY = kMaxStickValue - *outY;
    }

    // Apply smoothing (exponential moving average) if enabled
    bool smoothingEnabled = FUN_00410eb0();
    if (!smoothingEnabled)
    {
        float smoothFactor = kSmoothFactor; // typically in 0..1
        float oneMinusSmooth = kMaxStickValue - kSmoothFactor;

        // Smooth outX using stored previous value at offset 0x60
        if ((float)((uint)*outX & kDeadZoneMask) < (float)((uint)*(float*)(thisObj + 0x60) & kDeadZoneMask))
        {
            *outX = *(float*)(thisObj + 0x60) * oneMinusSmooth + *outX * kSmoothFactor;
        }
        // Smooth outY using stored previous value at offset 0x64 (100 = 0x64)
        if ((float)((uint)*outY & kDeadZoneMask) < (float)((uint)*(float*)(thisObj + 100) & kDeadZoneMask))
        {
            *outY = *(float*)(thisObj + 100) * oneMinusSmooth + *outY * kSmoothFactor;
        }

        // Apply minimum deadzone after smoothing
        if ((float)((uint)*outX & kDeadZoneMask) < kMinOutputThreshold)
            *outX = 0.0f;
        if ((float)((uint)*outY & kDeadZoneMask) < kMinOutputThreshold)
            *outY = 0.0f;

        // Store smoothed values back to state
        *(float*)(thisObj + 0x60) = *outX;
        *(float*)(thisObj + 100)  = *outY;
    }
    else
    {
        // Smoothing disabled: clear stored values
        *(int*)(thisObj + 0x60) = 0;
        *(int*)(thisObj + 100)  = 0;
    }
}