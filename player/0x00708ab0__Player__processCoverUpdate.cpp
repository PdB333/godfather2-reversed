// FUNC_NAME: Player::processCoverUpdate
void __fastcall Player::processCoverUpdate(int *this)
{
    int iVar1;
    int iVar2;
    char cVar3;
    undefined4 uVar4;
    byte bVar5;
    int *piVar6;
    byte bVar7;
    byte bVar8;
    int *piVar9;
    int *unaff_ESI; // likely global or this pointer from caller
    float10 fVar10;
    float fVar11;
    float fVar12;
    undefined4 uStack_84;
    undefined4 uStack_80;
    undefined4 uStack_7c;
    float fStack_78;
    undefined4 uStack_74;
    undefined4 uStack_70;
    float fStack_6c;
    undefined4 uStack_68;
    undefined4 uStack_64;
    undefined4 uStack_60;
    undefined4 uStack_5c;
    undefined4 auStack_58[2];
    undefined1 local_50[12];
    undefined4 local_44;
    undefined4 local_34;
    undefined4 local_24;
    undefined4 uStack_20;
    float fStack_1c;
    undefined4 uStack_18;
    undefined4 local_14;

    // +0x74 flags bitmask (0x400 = coverEntered? 0x100 = inCover? 0x2000 = aiming? 0x200 = readyForNetworkUpdate?)
    if (((((uint)this[0x74] >> 10 & 1) != 0) && (this[0x6d] == 0)) &&
        (this[0x9f] + 2U < (uint)this[0x9e]))
    {
        this[0x74] = this[0x74] & 0xfffffbff; // clear bit10
        this[0x9e] = 0; // timer
    }
    this[0x9e] = this[0x9e] + 1; // increment timer

    // +0x74 bit8 (inCover?) and bit13 (hasTarget?) and target object exists
    if (((((uint)this[0x74] >> 8 & 1) != 0) && (this[0x6c] != 0)) &&
        (((uint)this[0x74] >> 0xd & 1) != 0))
    {
        local_44 = 0;
        local_34 = 0;
        local_24 = 0;
        local_14 = _DAT_00d5780c; // some global matrix
        FUN_00544180(this[0x6c] + 0xe0, local_50); // get target transform
        (**(code**)(*this + 0x28))(local_50); // vtable: probably getWorldMatrix or computeAimConstraint
        iVar1 = this[0x6c];
        // +0x9d stored distance/height
        if (fStack_1c <= (float)this[0x9d])
        {
            uStack_7c = uStack_20;
            uStack_74 = uStack_18;
            fStack_78 = (float)this[0x9d];
            (**(code**)(*this + 0x1c))(&uStack_7c); // vtable: setTargetPosition
            uStack_74 = uStack_80;
            uStack_70 = uStack_7c;
            fStack_6c = fStack_78;
            uStack_68 = 0;
            FUN_009f4c40(&uStack_74); // physics: apply force/impulse?
            iVar2 = this[0x6c];
            uStack_64 = 0;
            uStack_60 = 0;
            uStack_5c = 0;
            auStack_58[0] = 0;
            FUN_009f2000(); // update physics state?
            (**(code**)(*(int*)(iVar2 + 0xd0) + 0x40))(&uStack_64); // call a method on target's physics component
        }
    }

    // Global thresholds from DAT_012067e8, _DAT_00d613a8, _DAT_00d613a4
    fVar11 = DAT_012067e8 * _DAT_00d613a8;
    fVar12 = DAT_012067e8 * _DAT_00d613a4;
    if ((DAT_00e44598 < fVar12) && (DAT_00e44598 < fVar11))
    {
        // Compare current position (this+0x7c..0x7e) with target position (target+0x110)
        if (fVar12 < (float)((uint)((float)this[0x7c] - *(float*)(iVar1 + 0x110)) & DAT_00e44680))
            bVar8 = 0;
        else
            bVar8 = 8;
        if (fVar12 < (float)((uint)((float)this[0x7d] - *(float*)(iVar1 + 0x114)) & DAT_00e44680))
            bVar7 = 0;
        else
            bVar7 = 4;
        if (fVar12 < (float)((uint)((float)this[0x7e] - *(float*)(iVar1 + 0x118)) & DAT_00e44680))
            bVar5 = 0;
        else
            bVar5 = 2;
        // If all three differences are within tolerance (bits 2,4,8 = 0xe)
        if ((byte)(bVar5 | bVar7 | bVar8) == 0xe)
        {
            // Now check another tolerance using fVar11 and positions this+0x80..0x82 vs target+0x1b0
            if (fVar11 < (float)((uint)((float)this[0x80] - *(float*)(iVar1 + 0x1b0)) & DAT_00e44680))
                bVar8 = 0;
            else
                bVar8 = 8;
            if (fVar11 < (float)((uint)((float)this[0x81] - *(float*)(iVar1 + 0x1b4)) & DAT_00e44680))
                bVar7 = 0;
            else
                bVar7 = 4;
            if (fVar11 < (float)((uint)((float)this[0x82] - *(float*)(iVar1 + 0x1b8)) & DAT_00e44680))
                bVar5 = 0;
            else
                bVar5 = 2;
            if ((byte)(bVar5 | bVar7 | bVar8) == 0xe)
            {
                // All checks passed: enter/exit cover action
                FUN_00707cd0(); // enterCover
                this[0x74] = this[0x74] & 0xfffffaff; // clear bit9
                FUN_00707be0(); // exitCover? (or cover state transition)
                FUN_007073c0(); // setCoverState
            }
        }
    }

    FUN_007074a0(); // updateCoverTimer or related

    // Copy target world position to this->stored positions
    this[0x7c] = *(int*)(iVar1 + 0x110);
    this[0x7d] = *(int*)(iVar1 + 0x114);
    this[0x7e] = *(int*)(iVar1 + 0x118);
    this[0x7f] = *(int*)(iVar1 + 0x11c);
    this[0x80] = *(int*)(iVar1 + 0x1b0);
    this[0x81] = *(int*)(iVar1 + 0x1b4);
    this[0x82] = *(int*)(iVar1 + 0x1b8);
    this[0x83] = *(int*)(iVar1 + 0x1bc);

    // Check network object existence
    if (this[0x85] == 0)
        return;
    if (this[0x85] == 0x48) // some specific pointer value (maybe null sentinel)
        return;
    // Check flag bit9 (readyForNetworkUpdate)
    if (((uint)this[0x74] >> 9 & 1) == 0)
        return;

    piVar9 = this + 0x91; // m_moveDirection
    if ((((this[0x91] == 0) && (this[0x92] == 0)) && (this[0x93] == 0)) && (this[0x94] == 0))
        return;

    if (this[0x85] == 0)
        piVar6 = (int*)0x0;
    else
        piVar6 = (int*)(this[0x85] + -0x48); // adjust to get NetObject base

    uStack_84 = 0;
    cVar3 = (**(code**)(*piVar6 + 0x10))(0x55859efa, &uStack_84); // check network class ID?
    if (cVar3 == '\0')
        return;

    if (unaff_ESI == (int*)0x0)
        return;

    fVar10 = (float10)(**(code**)(*unaff_ESI + 0x1c0))(); // get current game time
    fVar12 = (float)fVar10;
    fVar11 = (float)this[0x9b]; // last sent time
    if ((fVar12 < fVar11) || (fVar11 < (float)this[0x9c] || fVar11 == (float)this[0x9c]))
    {
        if ((fVar11 <= fVar12) || ((float)this[0x9c] < fVar11))
            goto LAB_00708f5f;
        FUN_004df590(); // begin send reliable
        piVar9 = this + 0x8d;
        cVar3 = FUN_00414d50(); // check rate limit
        if (cVar3 != '\0')
            goto LAB_00708f5f;
    }
    else
    {
        FUN_004df590(); // begin send reliable
    }

    uVar4 = FUN_00471610(); // get network ID
    FUN_0044b4e0(auStack_58, uVar4); // pack message
    uVar4 = (**(code**)(*this + 0x58))(0, this, 0xffffffff, 0); // vtable: create remote event (script method?)
    uVar4 = FUN_004df330(&stack0xffffff78, piVar9, auStack_58, uVar4); // finalize message
    FUN_00414db0(uVar4); // add to send queue
    FUN_00414df0(); // flush queue

LAB_00708f5f:
    this[0x9c] = (int)fVar12; // update last update time
    return;
}