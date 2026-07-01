// FUNC_NAME: TweenInterpolator::update
void __thiscall TweenInterpolator::update(TweenData* this, float param2, float param3) {
    float fVar1;
    // +0x04: mode (0 or 1)
    if (*(int*)((char*)this + 0x04) == 1) {
        // +0x14: numerator, +0x0C: denominator1, +0x18: lastTime, +0x08: currentValue
        fVar1 = (*(float*)((char*)this + 0x14) / *(float*)((char*)this + 0x0C)) *
                (DAT_01205228 - *(float*)((char*)this + 0x18)) +
                *(float*)((char*)this + 0x08);
    } else {
        // +0x10: denominator2
        fVar1 = *(float*)((char*)this + 0x08) -
                (DAT_01205228 - *(float*)((char*)this + 0x18)) / *(float*)((char*)this + 0x10);
    }
    // +0x08: currentValue
    *(float*)((char*)this + 0x08) = fVar1;
    float fVar2 = _DAT_00d5780c;
    if (fVar1 < _DAT_00d5780c) {
        fVar2 = 0.0f;
        if (fVar1 > 0.0f) goto LAB_008de686;
        // +0x00: finished (0 = false)
        *(int*)((char*)this + 0x00) = 0;
    } else {
        // +0x00: finished (1 = true)
        *(int*)((char*)this + 0x00) = 1;
    }
    *(float*)((char*)this + 0x08) = fVar2;
LAB_008de686:
    // +0x18: lastTime
    *(float*)((char*)this + 0x18) = DAT_01205228;
    // +0x10: denominator2 = param2
    *(float*)((char*)this + 0x10) = param2;
    // +0x0C: denominator1 = param3
    *(float*)((char*)this + 0x0C) = param3;
}