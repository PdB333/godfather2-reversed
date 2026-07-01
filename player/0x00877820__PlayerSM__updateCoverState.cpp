// FUNC_NAME: PlayerSM::updateCoverState
bool __fastcall PlayerSM::updateCoverState(int *this)
{
    float fVar1;
    int iVar2;
    int iVar3;
    uint uVar4;
    float local_1c4;
    float fStack_1dc;
    float fStack_1d8;
    int iStack_1cc;
    float fStack_1c8;
    float local_1c4_00;
    undefined **ppuStack_1c0;
    float fStack_1bc;
    undefined **ppuStack_1b8;
    float fStack_1b0;
    float fStack_1ac;
    float fStack_1a8;
    float fStack_1a4;
    undefined **ppuStack_1a0;
    float fStack_19c;
    undefined **ppuStack_198;
    undefined1 auStack_194[4];
    undefined1 local_190[12];
    undefined4 local_184;
    undefined4 local_174;
    undefined4 local_164;
    undefined **local_154;
    undefined **ppuStack_150;
    undefined1 auStack_144[16];
    undefined **ppuStack_134;
    undefined4 uStack_130;
    undefined4 uStack_124;
    undefined4 uStack_104;
    int iStack_100;
    int iStack_f4;
    undefined **ppuStack_e4;
    undefined **ppuStack_e0;
    undefined1 auStack_d4[16];
    undefined **ppuStack_c4;
    undefined4 uStack_c0;
    undefined4 uStack_b4;
    undefined4 uStack_94;
    int iStack_84;
    undefined1 local_6c[8];
    undefined1 auStack_64[96];

    // Get the player's current cover state from the cover state manager
    local_1c4 = *(float *)(this[0xd8] + 0x108) * _DAT_00d5c458; // +0x108: cover state timer
    local_184 = 0;
    local_174 = 0;
    local_164 = 0;
    local_154 = _DAT_00d5780c; // null pointer constant
    FUN_00470f80(local_190); // some initialization function
    (**(code **)(*this + 0x4c))(local_6c); // vtable call: get some state
    ppuStack_e4 = &PTR_FUN_00e32a8c;
    iStack_84 = 0;
    ppuStack_c4 = _DAT_00d5780c;
    uStack_c0 = 0xffffffff;
    uStack_94 = 0;
    uStack_b4 = 0xffffffff;
    ppuStack_e0 = _DAT_00d5780c;
    iVar3 = FUN_00471610(); // get some manager/component
    uVar1 = *(undefined8 *)(iVar3 + 0x30); // +0x30: position/vector
    fVar2 = *(float *)(iVar3 + 0x38); // +0x38: some float (maybe height)
    local_1c4 = 0.0;
    ppuStack_1c0 = _DAT_00d5780c;
    ppuStack_1b8 = _DAT_00d5780c;
    FUN_0056b420(auStack_194, &local_1c4, &fStack_1a4); // some math function
    fStack_1dc = (float)uVar1;
    fStack_1a8 = fVar2 + fStack_19c;
    fStack_1d8 = (float)((ulonglong)uVar1 >> 0x20);
    _fStack_1b0 = CONCAT44((fStack_1d8 + (float)ppuStack_1a0) - _DAT_00d765e0, fStack_1dc + fStack_1a4);
    FUN_00542650(&stack0xfffffe18, &fStack_1b0, 2, 0x80000000, 0, 0); // raycast/line test
    FUN_009e5ed0(auStack_64, &ppuStack_e4); // cleanup/end of some scope
    iStack_1cc = 1; // default cover state: low cover
    if (iStack_84 == 0) {
        (**(code **)(*this + 0x54))(1); // vtable: set cover state to low
        (**(code **)(*this + 0x5c))(0x80, 0xc0); // vtable: set some flags
        return false;
    }
    iVar3 = FUN_00542700(auStack_d4); // get hit result
    if ((iVar3 != 0) && ((*(uint *)(iVar3 + 4) & 0x800) != 0)) {
        iStack_1cc = 2; // high cover
    }
    ppuStack_134 = _DAT_00d5780c;
    ppuStack_150 = _DAT_00d5780c;
    fStack_1bc = DAT_00e44564 - fStack_1c8; // some offset calculation
    local_154 = &PTR_FUN_00e32a8c;
    iStack_f4 = 0;
    uStack_130 = 0xffffffff;
    uStack_104 = 0;
    uStack_124 = 0xffffffff;
    iVar3 = FUN_00471610(); // get some manager/component
    uVar1 = *(undefined8 *)(iVar3 + 0x30); // +0x30: position/vector
    fVar2 = *(float *)(iVar3 + 0x38); // +0x38: some float
    fStack_1a4 = 0.0;
    ppuStack_1a0 = _DAT_00d5780c;
    fStack_19c = fStack_1bc;
    ppuStack_198 = _DAT_00d5780c;
    FUN_0056b420(auStack_194, &fStack_1a4, &local_1c4); // some math function
    fStack_1dc = (float)uVar1;
    fStack_1a8 = fVar2 + fStack_1bc;
    fStack_1d8 = (float)((ulonglong)uVar1 >> 0x20);
    _fStack_1b0 = CONCAT44((fStack_1d8 + (float)ppuStack_1c0) - _DAT_00d765e0, fStack_1dc + local_1c4);
    FUN_00542650(&stack0xfffffe18, &fStack_1b0, 2, 0x80000000, 0, 0); // raycast/line test
    FUN_009e5ed0(auStack_64, &local_154); // cleanup/end of some scope
    iVar3 = 1;
    uVar5 = 0x80;
    if (((iStack_f4 != 0) && (iVar4 = FUN_00542700(auStack_144), uVar5 = 0x80, iVar4 != 0)) &&
        ((*(uint *)(iVar4 + 4) & 0x800) != 0)) {
        iVar3 = 2;
        uVar5 = 0x40;
    }
    if (iStack_1cc != iVar3) {
        iStack_1cc = 0; // no cover
    }
    (**(code **)(*this + 0x54))(iStack_1cc); // vtable: set cover state
    (**(code **)(*this + 0x5c))(uVar5 | (uint)fVar2, 0xc0); // vtable: set some flags
    return iStack_100 != 0;
}