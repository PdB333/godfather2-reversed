// FUNC_NAME: JoystickDirectionProcessor::updateDirection
void JoystickDirectionProcessor::updateDirection(int dirIndex, float* axisValues)
{
    // +0x11c: flags (bit 28: stick input enabled? bit 27: maybe inverted?)
    // +0x130: angle threshold for x-axis (or deadzone center for x)
    // +0x134: angle threshold for y-axis
    // +0x1e4: deadzone radius x?
    // +0x1e8: deadzone radius y?
    // +0x1e0: current digital direction (0 = none, 1 = up?, 3 = down?)
    // +0x1dd: hold counter (debounce timer)

    uint flags = *(uint*)(this + 0x11c);
    float axisX = axisValues[0];
    float axisY = axisValues[1];
    float thresholdX = *(float*)(this + 0x130);
    float thresholdY = *(float*)(this + 0x134);
    float deadzoneX = *(float*)(this + 0x1e4);
    float deadzoneY = *(float*)(this + 0x1e8);

    // Check if stick is within dead zone (with wrap-around handling for analog sticks)
    // bit 28 must be set for this deadzone logic to apply
    if (((flags >> 0x1c) & 1) == 0 ||
        (deadzoneX >= 0.0f &&
         (float)((uint)(axisY - thresholdY) & DAT_00e44680) <= deadzoneX))
    {
        // Either deadzone check didn't apply (bit 28 clear) or axisY close to center
        // Similarly for axisX
        if (deadzoneY >= 0.0f &&
            deadzoneY <= (float)((uint)(axisX - thresholdX) & DAT_00e44680))
        {
            // If both axes are within deadzone? Actually this condition seems inverted.
        }
        else {
            // If axisX difference is within deadzoneY range? This logic is tricky.
            // Possibly it's checking if either axis is outside deadzone.
        }
    }

    // Original decompiled logic reorganized:
    bool deadzoneActive = (flags >> 0x1c) & 1;
    bool outsideDeadzone = false;
    if (deadzoneActive)
    {
        // Check if axisY is within the deadzone (wrapped)
        float diffY = axisY - thresholdY;
        uint bitsY = *(uint*)&diffY;   // reinterpret as uint
        bitsY = bitsY & DAT_00e44680;  // mask
        float wrappedDiffY = *(float*)&bitsY;
        if (deadzoneX >= 0.0f && wrappedDiffY <= deadzoneX)
        {
            // axisY is inside deadzone, now check axisX
            float diffX = axisX - thresholdX;
            uint bitsX = *(uint*)&diffX;
            bitsX = bitsX & DAT_00e44680;
            float wrappedDiffX = *(float*)&bitsX;
            if (deadzoneY >= 0.0f && wrappedDiffX <= deadzoneY)
            {
                // Both axes inside deadzone -> no direction
                outsideDeadzone = false;
            }
            else
            {
                outsideDeadzone = true;
            }
        }
        else
        {
            outsideDeadzone = true;
        }
    }
    else
    {
        outsideDeadzone = false; // deadzone disabled
    }

    if (outsideDeadzone)
    {
        // Input is outside deadzone, determine direction based on y-axis relative to threshold
        if (axisY >= thresholdY) // Actually original: param_3[1] >= *(float*)(this+0x134)
        {
            dirIndex = 3; // e.g., "down" or "right"
        }
        else
        {
            dirIndex = 1; // e.g., "up" or "left"
        }
    }
    else
    {
        // Inside deadzone, check if we need to clear the direction
        if (((flags >> 0x1b) & 1) == 0) // bit 27
        {
            if (*(int*)(this + 0x1e0) == 0)
                return;
            *(int*)(this + 0x1e0) = 0;
            *(byte*)(this + 0x1dd) = 0;
            FUN_0094a5c0(); // notify direction cleared
            return;
        }
        // else: bit 27 is set, do nothing (stay in previous direction?)
    }

    // Debounce logic: if the new direction matches current, reset counter; else increment
    if (*(int*)(this + 0x1e0) == dirIndex)
    {
        *(byte*)(this + 0x1dd) = 0;
    }
    else
    {
        *(byte*)(this + 0x1dd) += 1;
        if (*(byte*)(this + 0x1dd) > 7)
        {
            *(int*)(this + 0x1e0) = dirIndex;
            *(byte*)(this + 0x1dd) = 0;
            FUN_0094a5c0(); // notify direction changed
            return;
        }
    }
}