// FUNC_NAME: PlayerActionHandler::handleAction
// Address: 0x007ce990
// This function processes player action commands (actionId) with deltaTime and other parameters.
// It manages a state machine for player actions, including weapon handling, combat, vehicle, and mission interactions.

undefined1 __thiscall PlayerActionHandler::handleAction(int *this, undefined4 arg0, float deltaTime, undefined4 arg3, int actionId, undefined4 arg5)
{
    undefined4 uVar1;
    char cVar2;
    undefined4 *puVar3;
    int iVar4;
    int iVar5;
    int *piVar6;
    int *piVar7;
    bool bVar8;
    float10 fVar9;
    undefined1 returnVal; // local_21
    undefined4 uStack_18;
    int local_10; // linked list node
    undefined4 local_c;
    int local_8; // linked list node
    undefined4 local_4;

    // Linked list manipulation for action tracking
    iVar4 = this[0x16]; // +0x58: pointer to some object (e.g., entity)
    returnVal = 1;
    local_10 = 0;
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    if ((iVar4 != 0) && (iVar4 + 0x48 != 0)) {
        local_c = *(undefined4 *)(iVar4 + 0x4c); // +0x4c: next pointer
        *(int **)(iVar4 + 0x4c) = &local_10;
        local_10 = iVar4 + 0x48; // +0x48: prev pointer
    }
    piVar6 = this + 0x6d; // +0x1B4: pointer to action list head
    if (((&local_8 != piVar6) && (iVar4 = *piVar6, iVar4 != 0)) &&
       (local_4 = 0, local_8 = iVar4, iVar4 != 0)) {
        local_4 = *(undefined4 *)(iVar4 + 4); // +4: next pointer
        *(int **)(iVar4 + 4) = &local_8;
    }

    switch(actionId) {
    case 0x31: // 49 - e.g., "start action"
        if (*(char *)(this[0x16] + 0xff8) == '\0') { // +0xff8: some flag
            FUN_006f8d00(); // likely play sound or effect
        }
        break;
    case 0x32: // 50
        FUN_007ce2e0(); // likely handle specific action
        break;
    case 0x33: // 51
    case 0x36: // 54
    case 0x38: // 56
    case 0x3b: // 59
    case 0x3c: // 60
        break; // no-op
    case 0x34: // 52
        puVar3 = (undefined4 *)FUN_007ab160(); // get some manager
        (**(code **)*puVar3)(4); // virtual call with 4
        FUN_0045f2a0(0); // set something to 0
        break;
    case 0x35: // 53
        if ((*piVar6 != 0) && (*piVar6 != 0x48)) {
            if (*piVar6 == 0) {
                FUN_0071f580(); // handle null case
            } else {
                FUN_0071f580(); // handle non-null case (same function?)
            }
        }
        break;
    case 0x37: // 55
        FUN_007ce480(); // handle specific action
        break;
    case 0x39: // 57 - e.g., "interact"
        this[0x74] = this[0x74] | 0x10; // set flag bit 4
        cVar2 = FUN_007cc310(0); // check if action allowed
        if (cVar2 == '\0') {
            // Virtual call at offset 0x2c (likely play animation/effect)
            (**(code **)(*this + 0x2c))(0x46f5c7b4, 1, 1, 0, 0x3f800000, 0x3f800000);
        }
        if (*(char *)((int)this + 0x20e) != '\0') { // +0x20e: byte flag
            FUN_006915c0(0xc); // stop sound 0xc
            *(undefined1 *)((int)this + 0x20e) = 0;
        }
        if (*(char *)((int)this + 0x20d) != '\0') { // +0x20d: byte flag
            FUN_006915c0(0xb); // stop sound 0xb
            *(undefined1 *)((int)this + 0x20d) = 0;
        }
        break;
    default:
        returnVal = FUN_007abec0(arg0, deltaTime, arg3, actionId, arg5); // default handler
        break;
    case 0x3d: // 61 - e.g., "start aiming"
        FUN_007cc310(1); // enable action
        FUN_007cd370(this[0x70]); // start action with object at +0x1C0
        goto LAB_007ceb51;
    case 0x3e: // 62 - e.g., "fire weapon"
        cVar2 = (**(code **)(*(int *)this[0x70] + 0x18))(); // virtual: canFire?
        if (cVar2 != '\0') {
            FUN_007cc310(1);
            FUN_007cd370(this[0x70]);
            FUN_006913c0(0xc); // play sound 0xc
            *(undefined1 *)((int)this + 0x20e) = 1;
            cVar2 = (**(code **)(*(int *)this[0x70] + 0x20))(); // virtual: isAutoFire?
            if (cVar2 != '\0') {
                fVar9 = (float10)FUN_007cadc0(); // get fire rate
                this[0x71] = (int)(float)fVar9; // store fire timer
            }
        }
        if ((*piVar6 == 0) || (*piVar6 == 0x48)) break;
        goto LAB_007ceb62;
    case 0x3f: // 63 - e.g., "update fire timer"
        if (_DAT_00d577a0 < (float)this[0x71]) { // global threshold
            this[0x71] = (int)((float)this[0x71] - deltaTime); // decrement timer
        }
        break;
    case 0x40: // 64 - e.g., "handle vehicle interaction"
        if ((((uint)this[0x74] >> 6 & 1) == 0) && (cVar2 = FUN_007fd640(), cVar2 == '\0')) {
            FUN_007caf20(arg0, deltaTime); // handle vehicle action
        }
        break;
    case 0x41: // 65 - e.g., "switch weapon"
        FUN_007cafa0(); // reset current action
        iVar4 = FUN_006ec9a0(); // get current weapon index
        piVar7 = (int *)this[0x70]; // weapon object
        this[0x68] = iVar4; // store weapon index
        if ((*(short *)(piVar7[4] + 0x10) == 0) || // check weapon count
           (iVar4 = iVar4 * 0x2c + *(int *)(piVar7[4] + 4), iVar4 == 0)) break;
        *(undefined1 *)(this + 0x83) = 0; // clear byte at +0x20C
        FUN_007cc310(1);
        FUN_007cb810(); // setup weapon
        cVar2 = (**(code **)(*piVar7 + 0x24))(); // virtual: isWeaponReady?
        FUN_007ccfb0(iVar4, *(undefined4 *)(this[0x70] + 0x10), cVar2 != '\0'); // apply weapon
        if ((*(uint *)(iVar4 + 0x24) >> 8 & 1) == 0) { // check alt fire flag
            cVar2 = (**(code **)(*piVar7 + 0x24))();
            FUN_007cb6f0(iVar4, cVar2 == '\0'); // set weapon ready
            this[0x74] = this[0x74] & 0xfffffbff; // clear bit 10
        } else {
            FUN_007cb780(iVar4); // set alt fire
            this[0x74] = this[0x74] | 0x400; // set bit 10
        }
        cVar2 = (**(code **)(*piVar7 + 0x24))();
        if (cVar2 == '\0') {
            this[0x74] = this[0x74] | 1; // set bit 0
        }
        if ((*piVar6 == 0) || (*piVar6 == 0x48)) break;
        if (*piVar6 == 0) {
            iVar4 = 0;
        } else {
            iVar4 = *piVar6 + -0x48;
        }
        iVar4 = FUN_006ad770(iVar4); // get some index
        cVar2 = (**(code **)(*piVar7 + 0x24))();
        if (cVar2 != '\0') goto LAB_007ceb8f;
        if (iVar4 != 0) {
            cVar2 = FUN_0078af40();
            goto joined_r0x007cedbc;
        }
        goto LAB_007cedc2;
    case 0x42: // 66 - e.g., "cancel weapon switch"
        FUN_007cc090(1); // cancel action
        FUN_007cafa0(); // reset
        if (this[0x72] != 0) { // +0x1C8: some object
            FUN_00815060(this[0x72]); // destroy
            this[0x72] = 0;
        }
        *(undefined1 *)(this + 0x83) = 1; // set byte at +0x20C
        break;
    case 0x43: // 67 - e.g., "clear alt fire flag"
        this[0x74] = this[0x74] & 0xfffffbff; // clear bit 10
        break;
    case 0x44: // 68 - e.g., "update combat/action"
        if ((*piVar6 == 0) || (*piVar6 == 0x48)) break;
        arg0 = 0;
        cVar2 = (**(code **)(*(int *)this[0x70] + 0x14))(); // virtual: isWeaponEquipped?
        if (cVar2 != '\0') {
            cVar2 = (**(code **)(*(int *)this[0x70] + 0x24))(); // virtual: isWeaponReady?
            if (cVar2 == '\0') {
                FUN_007cdda0(); // start reload
            } else {
                arg0 = 1;
                FUN_007cdbd0(); // start fire
            }
        }
        if ((this[0x79] == 0) || ((char)this[0x83] == '\0')) { // +0x1E4 and +0x20C
            iVar4 = FUN_00624bd0(0x27a0f69c); // find entity by hash
            if ((iVar4 == 0) && (((uint)this[0x74] >> 0x13 & 1) != 0)) { // bit 19
                iVar4 = this[0x16];
                *(undefined8 *)(iVar4 + 0x424) = 0; // clear some fields
                *(undefined4 *)(iVar4 + 0x42c) = 0;
                this[0x74] = this[0x74] & 0xfff7ffff; // clear bit 19
            }
        } else {
            if ((float)this[0x7a] <= deltaTime && deltaTime != (float)this[0x7a]) { // +0x1E8
                bVar8 = ((uint)this[0x74] >> 0x14 & 1) != 0; // bit 20
                iVar4 = FUN_00624bd0(0x27a0f69c);
                if (iVar4 == 0) {
                    if ((((uint)this[0x74] >> 0x12 & 1) == 0) && (((uint)this[0x74] >> 0x11 & 1) == 0)) // bits 18,17
                    {
                        FUN_00470230(this[0x16], DAT_00e445fc, 0); // apply damage
                        this[0x74] = this[0x74] | 0x20000; // set bit 17
                        bVar8 = true;
                    }
                    cVar2 = FUN_007fd640(); // is in vehicle?
                    uVar1 = DAT_00d5ef84;
                    if (cVar2 != '\0') {
                        *(undefined4 *)(this[0x16] + 0x101c) = DAT_00d5ef84;
                        if (*piVar6 == 0) {
                            uRam0000101c = uVar1;
                        } else {
                            *(undefined4 *)(*piVar6 + 0xfd4) = uVar1;
                        }
                    }
LAB_007ceff3:
                    if (!bVar8) goto LAB_007cf11f;
                } else {
                    FUN_007554a0(DAT_01206800); // some function
                    if ((((uint)this[0x74] >> 0x12 & 1) != 0) || (((uint)this[0x74] >> 0x11 & 1) != 0))
                        goto LAB_007ceff3;
                    FUN_00470130(iVar4 + 0x68, DAT_00e445fc, 0); // apply damage to entity
                    this[0x74] = this[0x74] | 0x20000;
                }
                FUN_008042b0(); // update something
                iVar4 = FUN_0045eea0(); // get player entity
                iVar5 = FUN_00625050(0x187b7e2b, 0); // find entity by hash
                if ((iVar5 != 0) && (*(int *)(iVar5 + 0xa4) != 0)) {
                    iVar4 = *(int *)(iVar5 + 0xa4);
                }
                if (*piVar6 == 0) {
                    piVar7 = (int *)0x0;
                } else {
                    piVar7 = (int *)(*piVar6 + -0x48);
                }
                (**(code **)(*piVar7 + 0x14c))(iVar4, 0, 0); // virtual call
                if (*piVar6 == 0) {
                    piVar7 = (int *)0x0;
                } else {
                    piVar7 = (int *)(*piVar6 + -0x48);
                }
                (**(code **)(*piVar7 + 0x178))(DAT_01206800, 1); // virtual call
                this[0x74] = this[0x74] & 0xffefffff; // clear bit 20
                if (((uint)this[0x74] >> 0xe & 1) != 0) { // bit 14
                    FUN_007f6420(0x48); // play sound 0x48
                    this[0x74] = this[0x74] & 0xffffbfff; // clear bit 14
                }
                this[0x74] = this[0x74] & 0xffffdfff; // clear bit 13
                piVar7 = (int *)this[0x16];
                iVar4 = FUN_0045eea0();
                if (this[0x73] != 0) { // +0x1CC
                    iVar4 = this[0x73];
                }
                (**(code **)(*piVar7 + 0x14c))(iVar4, 0, 0);
                (**(code **)(*piVar7 + 0x178))(uStack_18, 1);
            }
LAB_007cf11f:
            FUN_007cce00(this[0x79], this[0x7a]); // clear action
            this[0x79] = 0;
            this[0x7a] = 0;
        }
        cVar2 = FUN_0045eef0(); // is player alive?
        if ((cVar2 == '\0') && (cVar2 = FUN_0045f120(), cVar2 != '\0')) { // is in combat?
            FUN_007cb060(arg0); // update combat
        }
        cVar2 = FUN_0045eef0();
        if (((cVar2 == '\0') && (cVar2 = FUN_0045f120(), cVar2 != '\0')) &&
           (iVar4 = FUN_00625050(0x187b7e2b, 0), iVar4 != 0)) {
            FUN_007729f0(); // update AI
        }
        cVar2 = FUN_007f7c50(); // is in cover?
        if ((cVar2 == '\0') && (cVar2 = FUN_007fd640(), cVar2 != '\0')) { // is in vehicle?
            if (*piVar6 == 0) {
                iVar4 = 0;
            } else {
                iVar4 = *piVar6 + -0x48;
            }
            if (*(char *)(iVar4 + 0x1029) == '\0') { // some flag
                if (*piVar6 == 0) {
                    (**(code **)(iRam00000000 + 0x164))(); // virtual call
                } else {
                    (**(code **)(*(int *)(*piVar6 + -0x48) + 0x164))();
                }
            }
        }
        break;
    case 0x45: // 69 - e.g., "handle vehicle exit"
        if ((*piVar6 != 0) && (*piVar6 != 0x48)) {
            if (((uint)this[0x74] >> 0x15 & 1) != 0) { // bit 21
                FUN_007cc3d0(); // cancel action
                this[0x74] = this[0x74] & 0xffdfffff; // clear bit 21
            }
            cVar2 = FUN_007fd640(); // is in vehicle?
            if (cVar2 == '\0') {
                this[0x74] = this[0x74] & 0xfffbffff; // clear bit 18
            } else {
                this[0x74] = this[0x74] | 0x40000; // set bit 18
            }
            if ((((((uint)this[0x74] >> 0x12 & 1) == 0) && (((uint)this[0x74] >> 0x11 & 1) == 0)) &&
                (cVar2 = FUN_007f47a0(), cVar2 == '\0')) && // is not in vehicle?
               (cVar2 = FUN_0045eec0(0x9ff0adcc), cVar2 == '\0')) { // check state
                if (*piVar6 == 0) {
                    piVar6 = (int *)0x0;
                } else {
                    piVar6 = (int *)(*piVar6 + -0x48);
                }
                if (((uint)this[0x74] >> 0xd & 1) == 0) { // bit 13
                    fVar9 = (float10)FUN_00470230(this[0x16], DAT_01206800 * DAT_00d636b8, 0);
                    if (fVar9 == (float10)0) {
                        this[0x74] = this[0x74] | 0x20000; // set bit 17
                    }
                    FUN_007f6460(); // play sound
                    FUN_00800670(); // update vehicle
                    piVar6[0x25c] = piVar6[0x25c] & 0xfffff9ff; // clear bits
                } else {
                    cVar2 = FUN_0045eec0(&DAT_00ca9bea); // check state
                    if (cVar2 == '\0') {
                        this[0x74] = this[0x74] & 0xffffdfff; // clear bit 13
                        if (piVar6[0x849] == 0) { // +0x2124
                            iVar4 = 0;
                        } else {
                            iVar4 = *(int *)(piVar6[0x849] + 0x24);
                        }
                        if ((iVar4 != 0) && (piVar6 = (int *)FUN_00625050(0x187b7e2b, 0), piVar6 != (int *)0x0))
                        {
                            returnVal = (**(code **)(*piVar6 + 0x2c))(iVar4, 1, 1, 0, 0x3f800000, 0x3f800000);
                        }
                    } else {
                        (**(code **)(*piVar6 + 0x164))(); // virtual call
                    }
                }
            }
        }
        break;
    case 0x46: // 70
        FUN_007cd5e0(); // handle specific action
        break;
    case 0x47: // 71 - e.g., "switch weapon (no alt)"
        iVar4 = FUN_006ec9a0();
        this[0x68] = iVar4;
        if (((*(short *)(*(int *)(this[0x70] + 0x10) + 0x10) != 0) &&
            (iVar4 = iVar4 * 0x2c + *(int *)(*(int *)(this[0x70] + 0x10) + 4), iVar4 != 0)) &&
           (((uint)this[0x74] >> 5 & 1) == 0)) { // bit 5
            FUN_007cc310(1);
            FUN_007cb810();
            FUN_007ccfb0(iVar4, *(undefined4 *)(this[0x70] + 0x10), 0);
            FUN_007cb6f0(iVar4, 1);
        }
        this[0x74] = this[0x74] & 0xffffffdf; // clear bit 5
        break;
    case 0x48: // 72 - e.g., "select weapon"
        if (-1 < (short)this[0x75]) { // +0x1D4: weapon slot index
            iVar4 = (**(code **)(*(int *)this[0x70] + 0xc))((int)(short)this[0x75]); // virtual: getWeaponBySlot
            this[0x70] = iVar4;
            FUN_007cc090(0); // cancel action
        }
        FUN_007cafa0(); // reset
        if (*(char *)((int)this + 0x20e) != '\0') {
            FUN_006915c0(0xc);
            *(undefined1 *)((int)this + 0x20e) = 0;
        }
        FUN_00929ba0(); // update UI or something
        break;
    case 0x4d: // 77 - e.g., "start aiming (alt)"
        FUN_007cc310(1);
        FUN_007cd470(this[0x70]); // start aiming
LAB_007ceb51:
        FUN_006913c0(0xc); // play sound
        *(undefined1 *)((int)this + 0x20e) = 1;
LAB_007ceb62:
        if (*piVar6 == 0) {
            iVar4 = 0;
        } else {
            iVar4 = *piVar6 + -0x48;
        }
        iVar4 = FUN_006ad770(iVar4);
        if (iVar4 != 0) {
            cVar2 = FUN_0078af40();
joined_r0x007cedbc:
            if (cVar2 != '\0') {
LAB_007ceb8f:
                FUN_007cc1a0(); // play sound or effect
                break;
            }
        }
LAB_007cedc2:
        FUN_007f6420(0x3c); // play sound 0x3c
    }

    // Cleanup linked list nodes
    if (local_8 != 0) {
        FUN_004daf90(&local_8); // remove from list
    }
    if (local_10 != 0) {
        FUN_004daf90(&local_10); // remove from list
    }
    return returnVal;
}