// FUNC_NAME: WeaponAimComponent::updateAim

void __thiscall WeaponAimComponent::updateAim(int* thisPtr, float deltaTime, float* targetPos)
{
    // thisPtr is WeaponAimComponent*
    // offsets: +0x30 (0xC0) = aimState, +0x32 (0xC8) = someTargetPointer, +0x12 (0x48) = parentPointer, 
    // +0x2a (0xA8) = flags, +0x2f (0xBC) = someValue, +0x16 (0x58) = someObject

    int* transformPtr1 = (int*)FUN_00471610();  // get some transform/entity
    int* positionPtr = (int*)FUN_00471610();    // get another position/entity

    int* targetAimPtr;
    if ((thisPtr[0x30] == 0) || (thisPtr[0x30] == 0x48)) {
        targetAimPtr = thisPtr + 0x32;
    } else {
        int* somePtr = (int*)FUN_00471610();
        targetAimPtr = (int*)(somePtr + 0x30);
    }

    // scale delta time by global multiplier
    FUN_00470130(targetAimPtr, deltaTime * DAT_00d636b8, 0);

    // compute world-space offset from target to our position
    float dx = targetPos[0] - *(float*)(positionPtr + 0x30);
    float dy = targetPos[1] - *(float*)(positionPtr + 0x34);
    float dz = targetPos[2] - *(float*)(positionPtr + 0x38);

    // transform offset into local space using some rotation matrix (transformPtr1+0x10)
    float localOffset[3];
    FUN_004a07f0(localOffset, &dx, transformPtr1 + 0x10);  // likely multiply by inverse rotation

    // localOffset now has world-space? Actually after transform, but then we normalize
    float localDir[3];
    localDir[0] = localOffset[0];
    localDir[1] = localOffset[1];
    localDir[2] = localOffset[2];

    // normalize local direction (first pass)
    float norm[3];
    FUN_0056afa0(norm, localDir);  // normalize or cross? Let's assume normalize

    // second transform: get another local direction from some other object
    int* objPtr = (int*)FUN_00471610();
    float objDir[3];
    objDir[0] = *(float*)(objPtr + 0x00);  // maybe quaternion or rotation
    objDir[1] = *(float*)(objPtr + 0x04);
    objDir[2] = *(float*)(objPtr + 0x08);
    // normalize it
    float objNorm[3];
    FUN_0056afa0(objNorm, objDir);

    // normalize again (third time?) Actually it normalizes the localDir again? Redundant
    float finalDir[3];
    FUN_0056afa0(finalDir, localDir);

    // compute dot product between finalDir and objNorm
    float dot = finalDir[0] * objNorm[0] + finalDir[1] * objNorm[1] + finalDir[2] * objNorm[2];

    // clamp dot to range [g_minDot, g_maxDot]
    float clampedDot = dot;
    if (clampedDot > DAT_00d5ccf8) {
        clampedDot = _DAT_00d5780c;  // upper bound?
    } else if (clampedDot < g_minDot) {  // missing check? Actually code: if (fVar9 <= g_minDot) then set to g_minDot
        clampedDot = g_minDot;
    }
    // Actually the decompiled: if (fVar9 <= DAT_00d5ccf8) || (fVar11 = _DAT_00d5780c, _DAT_00d5780c <= fVar9) then set fVar9 = fVar11
    // That's weird. Let's read carefully:
    // fVar9 = dot; fVar11 = DAT_00d5ccf8 (lower bound); if (fVar9 <= fVar11) || (fVar11 = _DAT_00d5780c, _DAT_00d5780c <= fVar9) then fVar9 = fVar11;
    // So if dot <= lower OR upper <= dot, set to fVar11 which is either lower or upper? That's a clamp both sides. I'll implement proper clamp:
    float lower = DAT_00d5ccf8;
    float upper = _DAT_00d5780c;
    if (dot < lower) dot = lower;
    if (dot > upper) dot = upper;

    double angle = (double)dot;
    float clampedAngle = (float)angle;
    // modulo by 2*PI? (DAT_00d5eeec)
    if (clampedAngle >= DAT_00d5eeec) {
        clampedAngle -= DAT_00d5eeec;
    }
    if (clampedAngle > DAT_00d5f00c) {
        clampedAngle = DAT_00d5f00c - (clampedAngle - DAT_00d5f00c);  // reflect
    }

    // scale by global multiplier and send to some function
    FUN_007222f0(clampedAngle * _DAT_00d65228);

    // now handle aiming calculation
    int* aimTarget;
    if ((thisPtr[0x30] == 0) || (thisPtr[0x30] == 0x48)) {
        aimTarget = thisPtr + 0x32;
    } else {
        int* somePtr2 = (int*)FUN_00471610();
        aimTarget = (int*)(somePtr2 + 0x30);
    }

    int baseIndex;
    if (thisPtr[0x12] == 0) {
        baseIndex = 0;
    } else {
        baseIndex = thisPtr[0x12] - 0x48;  // get parent base
    }

    int aimResult = FUN_0075ced0(baseIndex, aimTarget, targetPos);
    unsigned int flags = thisPtr[0x2a];
    unsigned int someValue = (**(int (__thiscall**)(int))(*(int*)thisPtr[0x16] + 0x270))(thisPtr[0x16]); // vtable call
    int index = aimResult + (someValue & 0xff) * 5;

    int tableEntry;
    if ((flags >> 1 & 1) == 0) {
        // use first table
        tableEntry = *(int*)(&DAT_00e51a88 + index * 4);
    } else {
        tableEntry = *(int*)(&DAT_00e51a20 + index * 4);
    }

    int currentState = FUN_0045eea0();
    if (currentState != tableEntry) {
        // call virtual function to set state
        (**(code (__thiscall**)(int, int, int, int, int, int))(*thisPtr + 0x2c))(
            thisPtr, tableEntry, 1, 0, DAT_0112aea8, thisPtr[0x2f], 0x3f800000);
    }

    // call parent update
    if (thisPtr[0x12] != 0) {
        (**(code (__thiscall**)(int))(*(int*)(thisPtr[0x12] - 0x48) + 0x164))();
    } else {
        // null parent, call some global?
        (**(code (__thiscall**)(int))(0 + 0x164))(); // unlikely
    }
}