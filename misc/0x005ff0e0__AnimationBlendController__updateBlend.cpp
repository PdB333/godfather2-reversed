// FUNC_NAME: AnimationBlendController::updateBlend
// Address: 0x005ff0e0
// Reconstructed from Ghidra decompilation

void __thiscall AnimationBlendController::updateBlend(float* thisPtr) // thisPtr points to struct
{
    float blendFactor = 0.0f;
    float savedComponent3;
    float fVar1;

    // Check if animation weights/time values are non-zero (offsets 0x88 and 0x90)
    if ((thisPtr[0x22] != 0.0f) && (thisPtr[0x24] != 0.0f)) {
        fVar1 = thisPtr[0x31]; // Duration/scale? (offset 0xC4)

        if (fVar1 > 0.0f) {
            savedComponent3 = thisPtr[3]; // Save fourth component (offset 0xC)
            blendFactor = thisPtr[0x30] / fVar1; // Calculate blend factor from current time/total (offset 0xC0)

            // Interpolate first three components between current pose (indices 4,5,6) and target pose (indices 0x18,0x19,0x1A)
            thisPtr[0] = (thisPtr[4] - thisPtr[0x18]) * blendFactor + thisPtr[0x18];
            thisPtr[1] = (thisPtr[5] - thisPtr[0x19]) * blendFactor + thisPtr[0x19];
            thisPtr[2] = (thisPtr[6] - thisPtr[0x1A]) * blendFactor + thisPtr[0x1A];
            thisPtr[3] = (thisPtr[7] - thisPtr[0x1B]) * blendFactor + thisPtr[0x1B];

            // Restore original fourth component (likely not interpolated)
            thisPtr[3] = savedComponent3;
        }

        // Check a flag at offset 0x40 (byte)
        if (*((char*)(thisPtr + 0x10)) != '\0') {
            thisPtr[0x38] = 0.0f; // Reset state marker (offset 0xE0)
        }

        // Check state marker value (offset 0xE0)
        if (thisPtr[0x38] == 2.8026e-45f) { // Denormal indicating 'stop' or 'done' state
            bool conditionA = (thisPtr[0x3B] > thisPtr[0x30]) || (*((float*)0x00e4497c) <= blendFactor); // global pointer
            if (!conditionA) {
                // Check bitfield flags (offset 0xB4, treated as uint)
                uint flags = (uint)thisPtr[0x2D];
                if ((flags & 0x8) == 0) { // bit 3
                    if ((flags & 0x40) == 0) { // bit 6
                        thisPtr[0x3D] = thisPtr[0x3F]; // Copy values (offset 0xF4,0xFC)
                        thisPtr[0x3E] = thisPtr[0x3F]; // (offset 0xF8,0xFC)
                    }
                    if ((flags & 0x20) == 0) { // bit 5
                        thisPtr[0x40] = thisPtr[0x42]; // (offset 0x100,0x108)
                        thisPtr[0x41] = thisPtr[0x42]; // (offset 0x104,0x108)
                    }
                }
                thisPtr[0x38] = 0.0f; // Reset state marker
                if ((flags & 0x10) != 0) { // bit 4
                    thisPtr[0x44] = 0.0f; // (offset 0x110)
                    thisPtr[0x43] = 0.0f; // (offset 0x10C)
                    return;
                }
            }
            else {
                if ((((uint)thisPtr[0x2D]) >> 3 & 1) == 0) { // bit 3
                    FUN_005fef10(); // Called when condition fails and bit3 not set
                    return;
                }
            }
        }
        else {
            if (thisPtr[0x38] == 0.0f) {
                // Check conditions at offsets 0x94 and 0x9C
                if ((thisPtr[0x25] == 0.0f) || (thisPtr[0x27] == 0.0f)) {
                    FUN_005fea70(1); // Set state or error handling
                    return;
                }
                // If remaining time less than threshold, transition to next state
                if ((fVar1 - thisPtr[0x30]) < thisPtr[0x3B]) {
                    thisPtr[0x38] = 1.4013e-45f; // Denormal indicating 'transition requested'
                }
            }
            if ((((uint)thisPtr[0x2D]) >> 3 & 1) == 0) { // bit 3 not set
                FUN_005fef10(); // Continue or finalize
            }
        }
    }
}