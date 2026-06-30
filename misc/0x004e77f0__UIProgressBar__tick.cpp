// FUNC_NAME: UIProgressBar::tick
// Function at 0x004e77f0: Update tick for a progress bar style animated widget
// Handles progress value interpolation, state transition, and command list submission

void __thiscall UIProgressBar::tick(UIProgressBar* thisObj, float deltaMs)
{
    // Get style object from thisObj+0x24
    UIProgressBarStyle* style = *(UIProgressBarStyle**)(thisObj + 0x24);
    float styleDuration = *(float*)(style + 0x18); // style->duration

    // TLS pointer (FS:[0x2c]) – probably UI system context
    int* tlsPtr = *(int**)(__readfsdword(0x2c));
    int* contextPtr = *tlsPtr; // context pointer at *tlsPtr

    if ((DAT_00e2b05c < styleDuration) && (styleDuration < *(float*)(thisObj + 0x28))) {
        uint* flags = (uint*)(*(int*)(contextPtr + 8) + *(int*)(thisObj + 0x10));
        *flags |= 1; // Set dirty flag for redraw
    }

    int globalManager = DAT_01206880; // UI command list manager
    int styleInstance = *(int*)(thisObj + 0x24);

    // Check if redraw flag was set
    if ((*(byte*)(*(int*)(contextPtr + 8) + *(int*)(thisObj + 0x10)) & 1) == 0)
    {
        // No redraw needed
        if ((*(uint*)(styleInstance + 0x14) & 0x10) != 0) // style->flags & 0x10 (animated)
        {
            // Choose command type based on multiple conditions involving global flags
            if (((((*(uint*)(styleInstance + 0x14) & 0x200) == 0) ||
                  (*(byte*)(styleInstance + 0x11) == 0)) ||
                 (DAT_011947e4 == 0)) ||
                (((byte)DAT_011947e4 & *(byte*)(styleInstance + 0x11)) != 0))
            {
                **(undefined4**)(globalManager + 0x14) = &PTR_LAB_01124fd0; // command type A
            }
            else
            {
                **(undefined4**)(globalManager + 0x14) = &PTR_LAB_01124fe4; // command type B
            }
            // Append this object to the command list
            int* cmdPtr = (int*)(globalManager + 0x14);
            *cmdPtr = *cmdPtr + 4;
            *(int*)*cmdPtr = (int)thisObj;
            *cmdPtr = *cmdPtr + 4;
        }

        // Advance the progress time
        float newTime = *(float*)(thisObj + 0x28) + deltaMs;
        *(float*)(thisObj + 0x28) = newTime;

        // Determine target value for animation
        float targetValue;
        if ((*(int*)(thisObj + 0x34) == 1) && (*(int*)(thisObj + 0x38) == 0)) // state flags
        {
            // Interpolate using style parameters
            int* styleBase = *(int*)(thisObj + 0x24);
            float minVal = *(float*)(styleBase + 0x38); // style->min
            float rateA = *(float*)(styleBase + 0x2c);
            float baseA = *(float*)(styleBase + 0x28);
            float rateB = *(float*)(styleBase + 0x34);
            float baseB = *(float*)(styleBase + 0x30);
            float interpA = newTime * rateA + baseA;
            float interpB = newTime * rateB + baseB;
            float selected = (interpA < interpB) ? interpA : interpB;
            float maxVal = *(float*)(styleBase + 0x3c); // style->max
            if (minVal <= selected) {
                targetValue = selected;
                if (maxVal < selected) {
                    targetValue = maxVal;
                }
            } else {
                targetValue = minVal;
            }
        }
        else
        {
            // Call some effect stop function (sound? effect?)
            FUN_004ebc00(*(undefined4*)(thisObj + 4), 0);
            targetValue = deltaMs; // appears to set to deltaTime? Might be unintended; likely a bug? Actually careful: the code sets fVar6 = param_2; so targetValue = deltaMs
        }

        // Clamp targetValue to zero
        if (targetValue < 0.0f) {
            targetValue = 0.0f;
        }
        *(float*)(thisObj + 0x2c) = targetValue; // store interpolated value
    }
    else
    {
        // Redraw flag was set
        if ((*(byte*)(styleInstance + 0x14) & 0x10) != 0) // animated flag
        {
            // Push different command type and return early
            int* cmdPtr = (int*)(globalManager + 0x14);
            **(undefined4**)(globalManager + 0x14) = &PTR_LAB_01124fe4; // command type B
            *cmdPtr = *cmdPtr + 4;
            *(int*)*cmdPtr = (int)thisObj;
            *cmdPtr = *cmdPtr + 4;
            return;
        }
    }
}