// FUNC_NAME: AudioManager::updateAudioPriority
void __fastcall AudioManager::updateAudioPriority(void* this)
{
    int iVar1;
    bool bVar2;
    int iVar3;
    char cVar4;
    int iVar5;
    int iVar6;
    uint uVar7;
    int iVar8;
    undefined4 uVar9;
    bool bVar10;
    void* local_8; // linked list node pointer
    undefined4 local_4;

    // early exit if some state counter > 2
    if (3 < *(int*)((int)this + 0xd8)) { // +0xd8: state/counter
        return;
    }
    iVar1 = **(int**)(DAT_012233a0 + 4); // global pointer to something (likely player or camera)
    if ((iVar1 == 0) || (iVar1 == 0x1f30)) goto LAB_008b590b; // invalid/null or special sentinel

    // manipulate a temporary linked list (maybe for deferred cleanup?)
    local_8 = (void*)(iVar1 + -0x1ee8);
    local_4 = 0;
    if (local_8 != 0) {
        local_4 = *(undefined4*)(iVar1 + -0x1ee4);
        *(int*)(iVar1 + -0x1ee4) = &local_8;
    }

    // get two comparison values (maybe distances or priorities)
    iVar5 = FUN_008b4e20(0); // arg 0
    iVar6 = FUN_008b4e20(1); // arg 1

    iVar3 = DAT_01223484; // global audio manager or state
    // check if DAT_01223484 is valid and has bit1 at +0x37c set (maybe "is player in vehicle?")
    if (((DAT_01223484 == 0) || ((*(uint*)(DAT_01223484 + 0x37c) >> 4 & 1) == 0)) ||
        (bVar2 = true, *(int*)(DAT_01223484 + 0x3b4) == -1)) {
        bVar2 = false;
    }
    // bit 11 (0xb) of this+0x7c - possibly "cinematic mode" or "paused"
    if ((*(uint*)((int)this + 0x7c) >> 0xb & 1) == 0) {
        if (bVar2) {
            if ((DAT_01223484 == 0) || (bVar10 = true, *(int*)(DAT_01223484 + 0x3b4) == 0)) {
                bVar10 = false;
            }
        } else {
            bVar10 = iVar6 < iVar5;
        }
        FUN_0092e330(bVar10); // set some audio parameter (e.g., "is vehicle outside?")
    }

    iVar8 = iVar5;
    if (*(int*)(iVar1 + -0x3c) == 1) { // check if something is "active"
        iVar8 = iVar6;
        iVar6 = iVar5;
    }

    // based on cinematic flag, play different audio updates
    if ((*(uint*)((int)this + 0x7c) >> 0xb & 1) == 0) {
        FUN_00907a50(0, DAT_01205228); // 0 = default channel, value maybe volume
    } else if (iVar3 != 0) {
        FUN_008a2c00(0, DAT_01205228);
    }

    if (bVar2) {
        uVar7 = *(uint*)((int)this + 0x7c) >> 0xb;
        if (*(int*)(iVar1 + -0x3c) == *(int*)(iVar3 + 0x3b4)) { // same state as global
            if ((uVar7 & 1) == 0) {
                FUN_00907ac0(0x1e, 0x3f800000); // play sound 30 at full volume
            } else {
                FUN_008a2c50(0x1e, 0x3f800000);
            }
            if (*(char*)(iVar1 + 0x11ec) != '\0') { // flag
                uVar9 = 0x1c;
                if ((*(uint*)((int)this + 0x7c) >> 0xb & 1) == 0) goto LAB_008b583a;
                FUN_008a2c00(0x1c, 0x3f800000); // play sound 28
            }
        } else {
            if ((uVar7 & 1) == 0) {
                FUN_00907ac0(0x1d, 0x3f800000); // play sound 29
            } else {
                FUN_008a2c50(0x1d, 0x3f800000);
            }
            if (*(char*)(iVar1 + 0x11ec) != '\0') {
                uVar9 = 0x1b;
                if ((*(uint*)((int)this + 0x7c) >> 0xb & 1) == 0) {
LAB_008b583a:
                    FUN_00907a50(uVar9, 0x3f800000); // play sound category 27/28 at full volume
                } else {
                    FUN_008a2c00(0x1b, 0x3f800000); // play sound 27
                }
            }
        }
    } else {
        uVar7 = *(uint*)((int)this + 0x7c) >> 0xb;
        if (iVar6 < iVar8) { // comparison based on earlier swap
            if ((uVar7 & 1) == 0) {
                FUN_00907ac0(0x1d, 0x3f800000);
            } else if (iVar3 != 0) {
                FUN_008a2c50(0x1d, 0x3f800000);
            }
            if (*(char*)(iVar1 + 0x11ec) != '\0') {
                if ((*(uint*)((int)this + 0x7c) >> 0xb & 1) == 0) {
                    FUN_00907a50(0x1b, 0x3f800000);
                } else if (iVar3 != 0) {
                    FUN_008a2c00(0x1b, 0x3f800000);
                }
            }
        } else {
            if ((uVar7 & 1) == 0) {
                FUN_00907ac0(0x1e, 0x3f800000);
            } else if (iVar3 != 0) {
                FUN_008a2c50(0x1e, 0x3f800000);
            }
            if (*(char*)(iVar1 + 0x11ec) != '\0') {
                if ((*(uint*)((int)this + 0x7c) >> 0xb & 1) == 0) {
                    uVar9 = 0x1c;
                    goto LAB_008b583a;
                }
                if (iVar3 != 0) {
                    FUN_008a2c00(0x1c, 0x3f800000);
                }
            }
        }
    }

    if (local_8 != 0) {
        FUN_004daf90(&local_8); // cleanup linked list
    }

LAB_008b590b:
    // check if we should trigger an additional update
    if ((((*(uint*)((int)this + 0x188) >> 4 & 1) == 0) && // +0x188 bit4: flag
         (*(int*)(DAT_01223484 + 8) != 0)) &&
        (cVar4 = FUN_00481620(), cVar4 != '\0')) {
        FUN_008b3550(); // trigger another audio update
    }
    FUN_008ac2e0(); // final audio update
    return;
}