// FUNC_NAME: AnimationManager::updateAnimationState
int __thiscall AnimationManager::updateAnimationState(int this, int regEAX, int** ppInput, int inputIndex) {
    int* pAnimEntry;
    int* pAnimData;
    ushort tempFlags;
    bool bNegative;
    float deltaTime;
    float currentTime;
    float defaultTime;
    float timeDiff;
    int localStackVar;
    int result;
    int* pLocalArray;
    int localData;
    float localFloat;
    undefined4 localReturn;

    result = 0;
    // Check if animation data array exists, slot count within limit, and entry is allocated
    if ((*(int*)(this + 0x603c) != 0) && (ppInput[5] < (int*)0x200) &&
        (pAnimEntry = (int*)((int)ppInput[5] * 0x74 + *(int*)(this + 0x603c)), pAnimEntry != (int*)0x0) &&
        (pAnimData = *pAnimEntry, pAnimData != 0)) {
        currentTime = 0.0f;
        defaultTime = DAT_00e2b1a4; // Some default/initial time constant (likely 0.0 or a small epsilon)
        if ((*(byte*)(pAnimData + 7) & 1) != 0) { // Check bit0: active flag?
            int count = 0;
            if (regEAX != 0) {
                if (pAnimEntry + 0xf == (int*)0x0) {
                    count = 0;
                } else {
                    count = FUN_005e5900(pAnimEntry + 0xf); // Get some count from sub-structure
                }
                currentTime = (float)pAnimEntry[count + 0xf]; // Extract time from array
            }
            float blendTime = currentTime;
            if ((regEAX != 0) && (inputIndex = inputIndex + count * 0x30, (*(byte*)(inputIndex + 0x2c) & 1) != 0)) {
                if (ppInput[7] == (int*)0x0) {
                    FUN_00414c60(ppInput, inputIndex + 0x10, &pLocalArray); // Possibly allocate or copy
                    ppInput = &pLocalArray;
                }
                float fVar8 = (float)FUN_004bcfb0(ppInput); // Convert to float
                blendTime = fVar8;
            }
            timeDiff = blendTime - *(float*)(pAnimData + 8); // Subtract base time
            if (timeDiff >= 0.0f) {
                bNegative = false;
            } else {
                bNegative = true;
                float adjustedTime = timeDiff;
                if ((regEAX < 2) && (pAnimEntry != (int*)0xfffffff4)) {
                    FUN_005e5980(regEAX); // Handle some early state
                    adjustedTime = currentTime;
                }
                timeDiff = DAT_00e2b1a4;
                if ((*(byte*)(pAnimData + 7) & 2) == 0) { // Check bit1: loop flag?
                    pAnimEntry[0x15] = (int)DAT_00e2b1a4; // Reset timer
                } else {
                    FUN_005e5c60(pAnimEntry + 0xf, pAnimEntry[0x14], *(undefined4*)(pAnimData + 0x3c), pAnimEntry + 0x15); // Update blending
                    timeDiff = adjustedTime;
                }
            }
            pAnimEntry[0x14] = (int)blendTime; // Store blend time
            if ((bNegative) ||
                ((pAnimEntry[2] != 0 && (timeDiff = *(float*)(pAnimEntry[2] + 0x50), DAT_00e44598 < timeDiff)))) {
                // If negative or exceeding threshold, trigger animation action
                FUN_005e5b00(*(undefined4*)(pAnimData + 0xc), *(undefined4*)(pAnimData + 8), *(undefined4*)(pAnimData + 0x14));
            } else {
                timeDiff = 0.0f;
            }
        }
        // Assemble return flags from state
        localReturn._0_1_ = (byte)pAnimEntry[0x16];
        // Combine bit flags from offset 0x5A
        tempFlags = (*(byte*)((int)pAnimEntry + 0x5a) & 3) * 2;
        ushort combined = tempFlags | (ushort)(localReturn & 0xff01);
        localReturn = CONCAT22(localReturn._2_2_, combined);
        if ((char)tempFlags == 0x02) {
            localReturn = CONCAT22(localReturn._2_2_, combined) & 0xffffff9 | 0x80;
        }
        // Prepare output structure and call final update
        pLocalArray = pAnimEntry;
        localData = (int)pAnimData + 0x20;
        FUN_005f1f80(&pLocalArray); // Finalize state
        result = 1;
    }
    return result;
}