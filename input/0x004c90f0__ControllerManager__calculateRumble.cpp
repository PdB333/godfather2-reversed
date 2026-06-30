// FUNC_NAME: ControllerManager::calculateRumble
float __thiscall ControllerManager::calculateRumble(float inputSpeed) {
    float fVar1;
    float fVar2;
    float maxIntensity;
    float fVar6;
    float fVar7;
    int currentTick;
    int iVar4;
    int *slotPtr;
    int *thisPtr; // unaff_EDI

    thisPtr = (int *)this;
    currentTick = g_globalTickCount; // 0x01205224
    fVar7 = 0.0f;
    maxIntensity = 0.0f;

    // Check if this object and its slot array exist
    if ((*thisPtr != 0) && (thisPtr[0xa4] != 0)) { // +0x0 and +0x290 (0xa4*4)
        slotPtr = thisPtr + 6; // +0x18 start of rumble slot array (size 0x14 per slot)
        iVar4 = 32; // number of slots
        // Constant from global
        float one = g_oneConstant; // DAT_00e2b1a4 (likely 1.0f)

        do {
            // Check if slot is active (slotPtr[-2] = offset +0x10)
            if (slotPtr[-2] != 0) {
                // Base intensity from this object
                fVar1 = (float)thisPtr[0xb3]; // offset +0x2CC (0xb3*4)
                // Handle sign: treat as unsigned float
                if (thisPtr[0xb3] < 0) {
                    fVar1 = fVar1 + g_unsignedOffset; // DAT_00e44578 (0x100000000.0f)
                }
                fVar6 = fVar1;

                // Check slot type (slotPtr[-1] = offset +0x14) and time window
                if ((slotPtr[-1] == 1) && // type 1
                    ((uint)slotPtr[1] <= (uint)(currentTick - *slotPtr)) && // elapsed >= min (slotPtr[1] = +0x1C)
                    ((uint)(currentTick - *slotPtr) <= (uint)slotPtr[2])) { // elapsed <= max (slotPtr[2] = +0x20)
                    // Call unknown helper (maybe randomize)
                    FUN_005e6970();
                    // Threshold from this object
                    fVar2 = (float)thisPtr[0xb4]; // offset +0x2D0 (0xb4*4)
                    if (thisPtr[0xb4] < 0) {
                        fVar2 = fVar2 + g_unsignedOffset;
                    }
                    fVar6 = fVar1; // reset to base (though not needed if inputSpeed > threshold)
                    if (inputSpeed <= fVar2) {
                        // Scale intensity based on input speed
                        inputSpeed = inputSpeed / fVar2;
                        fVar6 = (one - inputSpeed) * fVar1;
                    }
                }
                // Track maximum intensity
                if (fVar7 < fVar6) {
                    fVar7 = fVar6;
                }
            }
            slotPtr += 5; // advance to next slot (5 ints = 0x14 bytes)
            iVar4--;
        } while (iVar4 != 0);
    }
    return fVar7;
}