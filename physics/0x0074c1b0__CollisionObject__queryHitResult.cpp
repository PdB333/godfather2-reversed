// FUNC_NAME: CollisionObject::queryHitResult
uint CollisionObject::queryHitResult(float someValue) {
    bool bVar1;
    float fVar2;
    uint uVar3;
    int iVar4;
    uint uVar5;

    fVar2 = DAT_01205228; // +0x? global time constant?
    uVar3 = *(uint *)(this + 0x8e8) >> 7; // bitfield at +0x8e8, shift to get bit 7
    if ((uVar3 & 1) == 0) {
        bVar1 = (someValue != DAT_00d5ccf8); // DAT_00d5ccf8 = 0.0f or invalid flag
        iVar4 = FUN_00471610(); // getGameTick()?
        uVar5 = FUN_00721d70(4, iVar4 + 0x30, DAT_00e51920, bVar1); // query object/effect
        uVar3 = uVar5;
        if ((uVar5 == 0) ||
            (((uVar3 = (uVar5 & 0xFFFF0000) | // preserve high word
              (((someValue == DAT_00d5ccf8) << 6) | // flags for equal
               ((std::isnan(someValue) || std::isnan(DAT_00d5ccf8)) << 2) |
               2U |
               (someValue < DAT_00d5ccf8)) << 8),
             someValue != DAT_00d5ccf8 &&
             (*(float *)(uVar5 + 0xc) <= someValue)) ||
            (*(float *)(uVar5 + 0xc) + _DAT_00e51924 <= fVar2))) {
            return uVar3 & 0xffffff00; // clear low byte (failure flag)
        }
    }
    return (uVar3 & 0xffffff00) | 1; // set low byte (success flag)
}