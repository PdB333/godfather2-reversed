// FUNC_NAME: PlayerSM::handleCommand
undefined1 __thiscall PlayerSM::handleCommand(int *this, int param_2, int param_3, int param_4, int command, float *param_6)
{
    uint *puVar1;
    int iVar2;
    float fVar3;
    float fVar4;
    char cVar5;
    undefined1 retVal;
    int *piVar7;
    undefined4 ediValue; // unaff_EDI
    undefined4 uVar8;
    float *pfStack24;
    float tempVars[5]; // local_14

    retVal = 1;
    switch(command - 0x23) // command range: 0x23 to 0x34
    {
        case 0: // command 0x23
            // If animController exists and is not a null pointer offset
            if ((this[0x22] != 0) && (this[0x22] != 0x48)) {
                iVar2 = this[0x17]; // owner/entity
                tempVars[1] = 0.0f;
                tempVars[0] = 0.0f;
                // Get model base pointer (subtract offset 0x48)
                if (this[0x22] == 0)
                    piVar7 = (int *)0x0;
                else
                    piVar7 = (int *)(this[0x22] - 0x48);
                pfStack24 = tempVars;
                // Call some virtual function on model (vtable offset 0x1f8)
                (**(code **)(*piVar7 + 0x1f8))(iVar2);
                if (this[0x22] == 0)
                    piVar7 = (int *)0x0;
                else
                    piVar7 = (int *)(this[0x22] - 0x48);
                uVar8 = (**(code **)(*piVar7 + 0x280))(&stack0xffffffe4);
                uVar8 = FUN_00875af0(iVar2, uVar8);
                // Call setAnimation on this? (vtable offset 0x2c)
                (**(code **)(*this + 0x2c))(uVar8, 1, 0, 0, 0x3f800000, 0x3f800000);
                return 1;
            }
            break;

        case 1: // command 0x24
            if ((this[0x22] != 0) && (this[0x22] != 0x48)) {
                if (this[0x22] == 0)
                    pfStack24 = (float *)0x0;
                else
                    pfStack24 = (float *)(this[0x22] - 0x48);
                FUN_00778b10(this[0x17]); // some stop/reset
                pfStack24 = (float *)&DAT_0112e028;
                FUN_00407e40(); // play sound?
                this[0x24] = this[0x24] | 1; // set flag bit0
                return 1;
            }
            break;

        case 2: // command 0x25
            if ((this[0x22] != 0) && (this[0x22] != 0x48)) {
                iVar2 = this[0x17];
                tempVars[1] = 0.0f;
                tempVars[0] = 0.0f;
                if (this[0x22] == 0)
                    piVar7 = (int *)0x0;
                else
                    piVar7 = (int *)(this[0x22] - 0x48);
                pfStack24 = tempVars;
                (**(code **)(*piVar7 + 0x1f8))(iVar2);
                cVar5 = FUN_008754b0(&stack0xffffffe4); // check some condition
                if (cVar5 == '\0')
                    uVar8 = 0x3af776c6; // animation hash?
                else if (this[0x22] == 0)
                    uVar8 = 0x50c3f3c6;
                else
                    uVar8 = 0x50c3f3c6;
                uVar8 = FUN_00875af0(iVar2, uVar8);
                (**(code **)(*this + 0x2c))(uVar8, 1, 0, 0, 0x3f800000, 0x3f800000);
                return 1;
            }
            break;

        case 3: // command 0x26
            if ((this[0x22] != 0) && (this[0x22] != 0x48)) {
                iVar2 = this[0x17];
                tempVars[3] = 0.0f;
                tempVars[2] = 0.0f;
                if (this[0x22] == 0)
                    piVar7 = (int *)0x0;
                else
                    piVar7 = (int *)(this[0x22] - 0x48);
                pfStack24 = tempVars + 2; // offset for 2nd vec
                (**(code **)(*piVar7 + 0x1f8))(iVar2);
                if (this[0x22] == 0)
                    piVar7 = (int *)0x0;
                else
                    piVar7 = (int *)(this[0x22] - 0x48);
                // Get position from model (vtable 0x1d8)
                (**(code **)(*piVar7 + 0x1d8))(tempVars, &stack0xffffffe4);
                FUN_005430c0(iVar2, &pfStack24); // set position?
                *(float **)(iVar2 + 0x860) = pfStack24; // copy pointer?
                *(undefined4 *)(iVar2 + 0x864) = ediValue;
                cVar5 = FUN_008754b0(&pfStack24);
                if (cVar5 == '\0')
                    uVar8 = 0x488999ae;
                else if (this[0x22] == 0)
                    uVar8 = 0xad385595;
                else
                    uVar8 = 0xad385595;
                uVar8 = FUN_00875af0(iVar2, uVar8);
                (**(code **)(*this + 0x2c))(uVar8, 0, 1, 0, 0x3f800000, 0x3f800000);
                return 1;
            }
            break;

        case 4: // command 0x27
            pfStack24 = (float *)0x77a0a0;
            (**(code **)(*(int *)this[0x17] + 0x260))(); // call some function on owner
            return 1;

        case 5: // command 0x28
            pfStack24 = (float *)0x77a0b2;
            FUN_00778c20();
            return 1;

        case 6: // command 0x29 - Update position with damping?
            if ((this[0x22] != 0) && (this[0x22] != 0x48)) {
                pfStack24 = tempVars + 2;
                FUN_00546730(); // get some vector?
                fVar4 = DAT_00e51cd0;
                this[0x25] = (int)(DAT_00e51cd0 * (float)this[0x25]);
                this[0x26] = (int)((float)this[0x26] * fVar4);
                this[0x27] = (int)((float)this[0x27] * fVar4);
                fVar3 = DAT_00e51ccc;
                this[0x25] = (int)((tempVars[2] - (float)this[0x28]) * fVar3 + (float)this[0x25]);
                this[0x26] = (int)((float)this[0x26] + (tempVars[3] - (float)this[0x29]) * fVar3);
                this[0x27] = (int)((float)this[0x27] + (tempVars[4] - (float)this[0x2a]) * fVar3);
                *(ulonglong *)(this + 0x28) = CONCAT44(tempVars[3], tempVars[2]); // store target pos
                this[0x2a] = (int)tempVars[4];
                return 1;
            }
            break;

        case 7: // command 0x2a - Compute velocity?
            if ((this[0x22] != 0) && (this[0x22] != 0x48)) {
                pfStack24 = (float *)this[0x17];
                tempVars[2] = (DAT_00e44564 - (float)this[0x25]) * DAT_00d5ef88;
                tempVars[3] = (DAT_00e44564 - (float)this[0x26]) * DAT_00d5ef88;
                tempVars[4] = (DAT_00e44564 - (float)this[0x27]) * DAT_00d5ef88;
                pfStack24 = (float *)FUN_00543050();
                FUN_007f7580(tempVars + 2);
                return 1;
            }
            break;

        case 8: // command 0x2b
            pfStack24 = (float *)0x77a268;
            FUN_007f75b0();
            return 1;

        case 9: // command 0x2c
            pfStack24 = (float *)0x77a27a;
            FUN_007796e0();
            return 1;

        case 10: // command 0x2d
            pfStack24 = (float *)0x77a28c;
            FUN_00779620();
            return 1;

        case 11: // command 0x2e
            pfStack24 = (float *)0x77a29e;
            FUN_00778e70();
            return 1;

        case 12: // command 0x2f - Enable something if flag
            if (((this[0x22] != 0) && (this[0x22] != 0x48)) && (((uint)this[0x24] >> 4 & 1) != 0)) // check bit4?
            {
                pfStack24 = (float *)0x77a2e7;
                FUN_00542d70();
                pfStack24 = (float *)0x1;
                FUN_0086d060(0); // enable index 0
                if (this[0x22] != 0) {
                    pfStack24 = (float *)0x77a303;
                    FUN_008621d0();
                    return 1;
                }
                pfStack24 = (float *)0x77a315;
                FUN_008621d0();
                return 1;
            }
            break;

        case 13: // command 0x30
            if (((this[0x22] != 0) && (this[0x22] != 0x48)) && (((uint)this[0x24] >> 4 & 1) != 0))
            {
                pfStack24 = (float *)0x77a35e;
                FUN_00542d70();
                pfStack24 = (float *)0x1;
                FUN_0086d060(1); // enable index 1
                if (this[0x22] != 0) {
                    pfStack24 = (float *)0x77a379;
                    FUN_008622a0();
                    return 1;
                }
                pfStack24 = (float *)0x77a38b;
                FUN_008622a0();
                return 1;
            }
            break;

        case 14: // command 0x31
            if ((this[0x22] != 0) && (this[0x22] != 0x48)) {
                if (this[0x22] != 0) {
                    puVar1 = (uint *)(this[0x22] + 0xee0); // set flag in anim controller
                    *puVar1 = *puVar1 | 0x1000;
                    return 1;
                }
                // else set global flag? (unusual)
                // uRam00000f28 = uRam00000f28 | 0x1000;
                return 1;
            }
            break;

        case 15: // command 0x32 - Clear bits
            this[0x24] = this[0x24] & 0xffffffdd; // clear bit1 and bit2? (0x22)
            return 1;

        case 16: // command 0x33 - Set bits
            this[0x24] = this[0x24] | 10; // set bit1 and bit3
            return 1;

        case 17: // command 0x34
            if ((this[0x22] != 0) && (this[0x22] != 0x48)) {
                if (this[0x22] != 0) {
                    pfStack24 = (float *)0x77a411;
                    // Call virtual on model base (offset 0x298)
                    (**(code **)(*(int *)(this[0x22] - 0x48) + 0x298))();
                    return 1;
                }
                pfStack24 = (float *)0x77a428;
                // (**(code **)(iRam00000000 + 0x298))();
                return 1;
            }
            break;

        default:
            pfStack24 = param_6;
            retVal = FUN_0073e610(param_2, param_3, param_4, command);
    }
    return retVal;
}