// FUNC_NAME: InputDeviceManager::processAnalogStickDeadzone
// Reconstructed from Ghidra at 0x006c9eb0
// This function applies deadzone and scaling to analog stick input (e.g., thumbsticks).
// It modifies the output float pointers (param_3 for X, param_4 for Y) based on deadzone thresholds param_5 and param_6.
// +0x6c: byte controller index (or -1 if disabled)
// Global flags and pointers control whether the stick is active.

void __thiscall InputDeviceManager::processAnalogStickDeadzone(
    int this,                           // param_1
    undefined4 param_2,                 // unknown (possibly flags or timestamp)
    float* outX,                        // param_3 - output X axis
    float* outY,                        // param_4 - output Y axis
    float deadzoneX,                    // param_5 - X deadzone threshold
    float deadzoneY)                    // param_6 - Y deadzone threshold
{
    int iVar1;
    float fVar2, fVar3, fVar4;
    float maxOutput = DAT_00e44564;      // Maximum output value (likely 1.0f or 32767.0f)
    float maxInputRange = _DAT_00d5780c; // Maximum raw input range (e.g., 32767.0f)

    // Early exit conditions:
    // If controller slot is -1 (disabled), or global flag is false,
    // or if a specific game mode (e.g., menu, cutscene) is active.
    if (*(int*)(this + 0x6c) == -1 ||
        DAT_00e50fb5 == '\0' ||
        (iVar1 = **(int**)(DAT_012233a0 + 4),      // globals pointer
         iVar1 != 0 &&
         (iVar1 != 0x1f30 && ((*(uint*)(iVar1 + 0x570) >> 0x14 & 1) != 0)))) {
        *outX = 0.0f;
        *outY = 0.0f;
        return;
    }

    // Call raw input retrieval function.
    // The first argument is the byte controller index from this+0x6c.
    // DAT_00d5ccf8 appears three times (likely default scale or deadzone values).
    FUN_00465e30(*(byte*)(this + 0x6c), param_2, outX, outY, 0, 0,
                 DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8);

    // Apply X-axis deadzone and scaling:
    fVar3 = maxOutput;
    fVar2 = maxInputRange;
    fVar4 = *outX;
    if (fVar3 - deadzoneX <= fVar4) {
        if (fVar4 <= deadzoneX) {
            // Within deadzone - zero out
            *outX = 0.0f;
            goto LAB_006c9f74;
        }
        // Positive side: subtract deadzone, scale to [0, maxInputRange - deadzoneX], then map to [0,1]?
        fVar4 = fVar4 - deadzoneX;
    } else {
        // Negative side: add deadzone (since fVar4 is negative below maxOutput-deadzoneX),
        // then scale similarly
        fVar4 = fVar4 + deadzoneX;
    }
    *outX = fVar4 / (fVar2 - deadzoneX);

LAB_006c9f74:
    // Apply Y-axis deadzone and scaling:
    fVar4 = *outY;
    if (fVar4 < fVar3 - deadzoneY) {
        // Negative side
        *outY = (fVar4 + deadzoneY) / (fVar2 - deadzoneY);
        return;
    }
    if (deadzoneY < fVar4) {
        // Positive side
        *outY = (fVar4 - deadzoneY) / (fVar2 - deadzoneY);
        return;
    }
    // Inside deadzone
    *outY = 0.0f;
    return;
}