// FUNC_NAME: PlayerSM::computeSmoothedValue
float10 __fastcall PlayerSM::computeSmoothedValue(PlayerSM* this)
{
    float local_4;
    
    // Branch based on a flag at offset 0x2BC (700 decimal)
    if (*(char*)((int)this + 0x2BC) == '\0') {
        // Default interpolation path: blend from m_current (0x110) toward m_target (0x114) using m_blendFactor (0x298)
        local_4 = *(float*)((int)this + 0x110);
        local_4 = (((*(float*)((int)this + 0x114) - local_4) * *(float*)((int)this + 0x298) + local_4) -
                    local_4) * *(float*)((int)this + 0x80) + local_4;
        // If there is an external source (pointer at 0x88), blend further with its value from some base constant
        if (*(int*)((int)this + 0x88) != 0) {
            float10 fVar2 = (float10)FUN_006c1070(*(int*)((int)this + 0x88));
            fVar2 = fVar2 * ((float10)local_4 - (float10)DAT_00d5efcc) + (float10)DAT_00d5efcc;
            return ((float10)local_4 - fVar2) * (float10)*(float*)((int)this + 0x298) + fVar2;
        }
    }
    else {
        // Alternate path: use m_timeParam (0x2DC) and range values (0x1C8 and 0x1D8)
        float fVar1 = *(float*)((int)this + 0x2DC);
        if (_DAT_00d5780c < fVar1) {
            // Beyond global threshold: extrapolate from m_current (0x110) toward m_farTarget (0x1D8)
            return (float10)((*(float*)((int)this + 0x1D8) - *(float*)((int)this + 0x110)) *
                            (fVar1 - _DAT_00d5780c) + *(float*)((int)this + 0x110));
        }
        // Within range: lerp between m_baseTarget (0x1C8) and m_current (0x110)
        local_4 = (*(float*)((int)this + 0x110) - *(float*)((int)this + 0x1C8)) * fVar1 +
                  *(float*)((int)this + 0x1C8);
    }
    return (float10)local_4;
}