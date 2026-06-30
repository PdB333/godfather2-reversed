// FUNC_NAME: ControllerInputManager::processThumbstickAxes
void __thiscall ControllerInputManager::processThumbstickAxes(ControllerInputManager* this, float* outAxes)
{
    // Constants from global data
    const float maxAxisValue = DAT_00e2b1a4;  // e.g., 1.0f
    const float deadzoneMin = DAT_00e44610;   // deadzone threshold
    const float deadzoneScale = DAT_00e4460c; // scale factor outside deadzone
    const float responseCurveFactor = DAT_00e2eff4; // interpolation factor for response curve

    // Raw axis values are passed in registers from caller:
    // unaff_retaddr = left X, unaff_EBX = left Y,
    // unaff_EBP = right X, unaff_ESI = right Y
    float rawLeftX = unaff_retaddr;
    float rawLeftY = unaff_EBX;
    float rawRightX = unaff_EBP;
    float rawRightY = unaff_ESI;

    // Read initial raw value for left X via input function (sets XMM0)
    FUN_0049ac70(0x12, 0x10); // reads left X into XMM0? Returns via XMM0
    float processedLeftX = in_XMM0_Da; // actually the value after call

    // Read another axis (maybe left Y) via input function
    FUN_0049ac70(0x13, 0x11); // reads left Y into XMM0? The result overwrites XMM0
    float fVar4 = maxAxisValue;
    if (in_XMM0_Da != 0.0f && processedLeftX != 0.0f)
    {
        fVar4 = DAT_00e2cd58; // alternate max value
    }

    // Apply deadzone to processedLeftX
    float deadzoned = (processedLeftX - deadzoneMin) * deadzoneScale;
    if (deadzoned > 0.0f)
    {
        if (maxAxisValue <= deadzoned)
            deadzoned = maxAxisValue;
    }
    else
    {
        deadzoned = 0.0f;
    }

    // Apply response curve (lerp between deadzoned and raw, smoothed)
    float finalLeftX = (fVar4 - fVar4 * responseCurveFactor) * deadzoned + fVar4 * responseCurveFactor;

    // Get vtable pointer from this object (+0x4 is vtable pointer? Actually dereferenced)
    int* vtable = *(int**)(this + 4); // offset +0x4: vtable pointer

    // Check mode for left X (axis index 0)
    int mode = ((int (*)(int))vtable[0x20 / 4])(0); // vtable entry at +0x20
    if (mode == 1 || mode == 2)
    {
        if (mode == 1)
            outAxes[0] = finalLeftX;
        else // mode == 2
            outAxes[0] = rawLeftX;
    }

    // Left Y
    mode = ((int (*)(int))vtable[0x20 / 4])(1);
    if (mode == 1 || mode == 2)
    {
        if (mode == 1)
            outAxes[1] = rawLeftY; // note: uses raw, not processed
        else // mode == 2
            outAxes[1] = rawLeftY; // actually same? Code: param_2[1] = unaff_retaddr; but that's left X? Wait re-examine.
    }
    // Actually code: iVar2 = (**(code **)(*piVar1 + 0x20))(1); if ((iVar2 == 1) || (unaff_retaddr = unaff_EBX, iVar2 == 2)) { param_2[1] = unaff_retaddr; }
    // So it writes unaff_retaddr which is assigned from unaff_EBX. So left Y is written directly.
    outAxes[1] = rawLeftY; // simplified: condition always true? See below

    // Similarly for right X and right Y
    mode = ((int (*)(int))vtable[0x20 / 4])(2);
    if (mode == 1 || (unaff_EBX = unaff_EBP, mode == 2)) // writes EBX then assign from EBP
    {
        outAxes[2] = rawRightX; // unaff_EBP assigned to unaff_EBX then assigned to out
    }
    else
    {
        // no else, writes only if condition true
    }

    mode = ((int (*)(int))vtable[0x20 / 4])(3);
    if (mode == 1)
    {
        outAxes[3] = unaff_EBP; // actually rawRightY? Wait unaff_EBP is right X, unaff_ESI is right Y
    }
    else if (mode == 2)
    {
        outAxes[3] = unaff_ESI; // right Y
    }
}
// Note: Due to register aliasing and decompiler artifacts, the exact mapping may differ.
// The function applies a deadzone + response curve to the left X axis only,
// and passes through all four raw axes with possible mode-dependent swapping.
// The caller sets the raw axis values in registers before calling this function.