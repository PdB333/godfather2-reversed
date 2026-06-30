// FUNC_NAME: UnknownClass::getBlendedValue
float __fastcall UnknownClass::getBlendedValue(void)
{
    float fVar1;
    long double blendResult;
    uint local_4;

    if (*(char *)(this + 0x2bc) == '\0') {
        // Not disabled: compute blended value using primary interpolation
        local_4 = *(float *)(this + 0xfc);                  // +0xfc = m_currentValueA
        // (targetValue - currentValueA) * blendFactor + currentValueA
        local_4 = (((*(float *)(this + 0x100) - local_4) * *(float *)(this + 0x298) + local_4)   // +0x100 = m_targetValueA, +0x298 = m_blendFactorA
                  - local_4) * *(float *)(this + 0x80) + local_4;                                 // +0x80 = m_secondaryBlendFactor
        if (*(int *)(this + 0x88) != 0) {                   // +0x88 = m_blendTargetPtr
            // Secondary blend from external target
            blendResult = (long double)FUN_006c1070(*(int *)(this + 0x88));
            blendResult = blendResult * ((long double)local_4 - (long double)DAT_00d5efd0) + (long double)DAT_00d5efd0;
            return (float)(((long double)local_4 - blendResult) * (long double)*(float *)(this + 0x298) + blendResult);
        }
    }
    else {
        // Disabled branch: use alternative interpolation
        fVar1 = *(float *)(this + 0x2dc);                   // +0x2dc = m_alternativeFactor
        if (_DAT_00d5780c < fVar1) {
            return (float)((*(float *)(this + 0x1cc) - *(float *)(this + 0xfc)) * (fVar1 - _DAT_00d5780c) + *(float *)(this + 0xfc));
        }
        local_4 = (*(float *)(this + 0xfc) - *(float *)(this + 0x1bc)) * fVar1 + *(float *)(this + 0x1bc);
    }
    return (float)local_4;
}