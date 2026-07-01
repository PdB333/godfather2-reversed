// FUNC_NAME: InputDeviceManager::updateAnalogInput
void __fastcall InputDeviceManager::updateAnalogInput(int this) {
    // this: offset +0x50 points to an input device object (e.g., raw controller)
    // +0x1ba: member within that device (e.g., dead zone config)
    const uint32 ABS_MASK = 0x7FFFFFFF; // clears sign bit for absolute value
    float axisReadings[3]; // stack buffer, actually three 4-byte values

    // Called at start
    inputInit();

    // Local variables initialized
    uint32 local_44 = 0;
    uint32 local_34 = 0;
    uint32 local_24 = 0;
    uint32 unknownConst = _DAT_00d5780c; // likely 0
    // These locals may be remnants of a larger struct; they are not used further.

    if (*(int *)(this + 0x50) != 0) {
        // Virtual call to read raw input from the device
        // vtable offset 0x90: likely GetRawAxisData
        int* device = *(int**)(this + 0x50);
        (*(void (**)(void*, void*, int))(*(int*)device + 0x90))(
            axisReadings, (char*)device + 0x1ba, 1);

        // Extract three axes from the raw buffer (may be X, Y, Z)
        uint32 rawX = *(uint32*)(axisReadings);      // uStack_3c
        float rawY = *(float*)(axisReadings + 4);    // fStack_38
        uint32 rawZ = *(uint32*)(axisReadings + 8); // local_34

        // Dead zone check: if any axis absolute value exceeds threshold
        float threshold = DAT_00d5ef84; // g_axisDeadZone
        bool anyExceeds = ((float)(rawX & ABS_MASK) > threshold) ||
                          ((float)((uint32)rawY & ABS_MASK) > threshold) ||
                          ((float)(rawZ & ABS_MASK) > threshold);

        float adjustedY;
        if (anyExceeds) {
            double doubleVal = (double)rawY; // convert to double
            FUN_00b9a9fa(); // probably clamp or scale
            adjustedY = (float)doubleVal;
        } else {
            adjustedY = 0.0f;
        }

        // Get other input source (e.g., keyboard)
        int otherInput = FUN_00471610(); // likely returns a structure
        float otherY = 0.0f;
        if (((float)(*(uint32*)(otherInput + 0x20) & ABS_MASK) > threshold) ||
            ((float)(*(uint32*)(otherInput + 0x24) & ABS_MASK) > threshold) ||
            ((float)(*(uint32*)(otherInput + 0x28) & ABS_MASK) > threshold)) {
            double doubleVal2 = (double)*(float*)(otherInput + 0x24);
            FUN_00b9a9fa(); // same scaling
            otherY = (float)doubleVal2;
        }

        // Blend analog and other input, then apply
        float delta = adjustedY - otherY;
        applyBlendedInput(delta, 1, DAT_00d5f520); // g_analogBlendFactor
    }
}