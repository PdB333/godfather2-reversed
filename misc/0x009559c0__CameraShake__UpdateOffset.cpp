// FUNC_NAME: CameraShake::UpdateOffset
void __thiscall CameraShake::UpdateOffset(float* outOffset) {
    float fVar1;
    char cVar2;
    float fVar3;
    double dVar4;
    double dVar5;
    float fVar6;
    float local_c;

    // +0x104: enabled flag (byte)
    cVar2 = *(char*)(this + 0x104);
    if ((cVar2 == '\0') && (*(float*)(this + 0xfc) <= g_ShakeThreshold)) {
        return;
    }

    // Use two different sets of amplitude data depending on frame comparison globals
    if ((g_SomeFrameCounter == g_FrameCompareA) ||
        ((g_SomeFrameCounter != g_FrameCompareB && (g_FrameCompareB <= g_SomeFrameCounter)))) {
        local_c = *(float*)(this + 0xf0); // +0xf0: amplitudeY2
        fVar6 = *(float*)(this + 0xec);   // +0xec: amplitudeX2
    }
    else {
        local_c = *(float*)(this + 0xf8); // +0xf8: amplitudeY1
        fVar6 = *(float*)(this + 0xf4);   // +0xf4: amplitudeX1
    }

    fVar1 = *(float*)(this + 0x94);       // +0x94: phase or frequency
    dVar4 = MathSin((double)fVar1);
    dVar5 = MathCos((double)fVar1);

    fVar3 = *(float*)(this + 0xb4) - *(float*)(this + 0xb8); // +0xb4: duration progress? +0xb8: start?
    if (*(float*)(this + 0xb8) <= fVar3) {
        fVar3 = *(float*)(this + 0xb8);
    }
    // Interpolation factor: clamp((durationProgress - start) / (end - start))
    local_c = (fVar3 / (*(float*)(this + 0xa8) - *(float*)(this + 0xb8))) * (fVar6 - local_c) + local_c;

    if (cVar2 == '\0') {
        if ((*(byte*)(g_SomeGlobal + 0x49) & 10) != 0) goto LAB_00955b01;
        local_c = *(float*)(this + 0xfc) - *(float*)(this + 0x100); // currentShake - shakeVelocity
        fVar6 = 0.0f;
        if (local_c <= 0.0f) goto LAB_00955af6;
    }
    else {
        fVar6 = *(float*)(this + 0x100) + *(float*)(this + 0xfc); // shakeVelocity + currentShake
        if (fVar6 < local_c) {
LAB_00955af6:
            local_c = fVar6;
        }
    }

    *(float*)(this + 0xfc) = local_c; // update current shake value

LAB_00955b01:
    // Combine with sine/cosine to produce output offset
    outOffset[0] = (float)dVar5 * *(float*)(this + 0xfc) + outOffset[0];
    outOffset[2] = outOffset[2] - (float)dVar4 * *(float*)(this + 0xfc);
    return;
}