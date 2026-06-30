// FUNC_NAME: EntityProcessor::processActionDispatch
// Function at 0x0073e610 - Dispatches various action events based on actionType parameter.
// The actionType is offset by 0x12, so cases correspond to actionType values 0x12..0x22.
// param_1 is 'this' pointer, param_2 unknown, param_3 is a float (distance?), param_4 unknown, param_5 is actionType, param_6 unknown.

undefined1 __thiscall EntityProcessor::processActionDispatch(int *thisPtr, undefined4 param_2, float param_3, undefined4 param_4, int actionType, undefined4 param_6)
{
    undefined1 retVal;
    int iVar2;
    int iVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    float fVar6;
    undefined4 uVar7;
    undefined4 uVar8;
    float local_94;
    undefined4 local_90;
    undefined1 *local_8c;
    undefined1 local_88;
    undefined1 local_84[4];
    undefined4 local_80;
    
    retVal = 1; // default success
    switch (actionType + -0x12) {
    case 0: // actionType == 0x12
        thisPtr[0x18] = 0; // offset +0x60: some state flag
        return 1;
    case 1: // actionType == 0x13
        FUN_007f63e0(0x5b); // play sound 0x5b
        FUN_005512c0(3);    // set some parameter (e.g., volume?)
        FUN_007fee80();     // flush/update audio
        return 1;
    case 2: // actionType == 0x14
        iVar3 = FUN_0072dc00(thisPtr[0x17]); // get object from pointer at +0x5C
        if (iVar3 != 0) {
            // check if global threshold <= object's field at +0xA8 <= thisPtr[0xc] (float at +0x30)
            if (((_DAT_00d577a0 <= *(float *)(iVar3 + 0xa8)) &&
                (*(float *)(iVar3 + 0xa8) <= (float)thisPtr[0xc])) &&
               ((*(int *)(iVar3 + 0x20) != 0 && ((*(uint *)(iVar3 + 0x4c) >> 1 & 1) != 0)))) {
                FUN_009979b0(1); // set some flag
            }
            fVar6 = *(float *)(iVar3 + 0xac);
            if ((_DAT_00d577a0 <= fVar6) && (fVar6 <= (float)thisPtr[0xc])) {
                fVar6 = (float)thisPtr[0xc] - fVar6;
                if (fVar6 < DAT_00e44598) {
                    // near threshold, deactivate components at +0x1E70 and +0x1E84 if non-zero
                    if (*(int *)(thisPtr[0x17] + 0x1e70) != 0) {
                        FUN_004df600(); // deactivate component
                    }
                    if (*(int *)(thisPtr[0x17] + 0x1e84) != 0) {
                        FUN_004df600(); // deactivate component
                    }
                }
                if (fVar6 < *(float *)(iVar3 + 0xb0)) {
                    local_94 = _DAT_00d5780c - fVar6 / *(float *)(iVar3 + 0xb0);
                    if (0.0 < local_94) {
                        if (_DAT_00d5780c <= local_94) {
                            local_94 = _DAT_00d5780c;
                        }
                        FUN_004706f0(local_94); // set alpha/opacity?
                        return 1;
                    }
                    FUN_004706f0(0);
                    return 1;
                }
                // if not in range, call something with +0x3C offset
                FUN_004088c0(thisPtr[0x17] + 0x3c);
                return 1;
            }
        }
        break;
    case 3: // actionType == 0x15
        FUN_0073e5e0(); // handle some state
        return 1;
    case 4: // actionType == 0x16
        iVar3 = thisPtr[0x17];
        iVar2 = FUN_00691810(); // get current context
        if (((iVar2 != 0) && (*(char *)(iVar2 + 0x1a8) == '\x03')) &&
           ((*(uint *)(iVar3 + 0x8e0) >> 10 & 1) != 0)) {
            FUN_00800960(); // start something
        }
        iVar3 = FUN_00732590(); // check something
        if (iVar3 != 0) {
            FUN_007ff050(1);
            return 1;
        }
        break;
    case 5: // actionType == 0x17
        FUN_0073e1a0(); // handle another action
        return 1;
    case 6: // actionType == 0x18
        iVar3 = FUN_0073e100(); // get some object
        if (iVar3 != 0) {
            FUN_0044b210(iVar3); // use object
            return 1;
        }
        break;
    case 7: // actionType == 0x19
        iVar3 = *thisPtr; // vtable?
        uVar4 = FUN_00735110(1,0,0,0x3f800000,0x3f800000); // create something?
        (**(code **)(iVar3 + 0x2c))(uVar4); // call vtable function at offset 0x2c
        uVar5 = 0;
        uVar4 = FUN_006fbc40(0,0); // get sound handle
        FUN_007f96a0(0x7ebe70b2,0,uVar4,uVar5); // play sound with ID 0x7ebe70b2
        FUN_006fbc70(); // release sound handle?
        return 1;
    case 8: // actionType == 0x1A
        if (**(int **)(DAT_012233a0 + 4) == 0) {
            iVar3 = 0;
        }
        else {
            iVar3 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
        }
        FUN_006ada80(0,0xffffffff); // some init
        local_80 = 0x10443534; // magic?
        FUN_0044b210(iVar3);
        local_90 = DAT_0112ad8c;
        local_8c = local_84;
        local_88 = 0;
        if (thisPtr[0x17] == 0) {
            iVar3 = 0;
        }
        else {
            iVar3 = thisPtr[0x17] + 0x3c;
        }
        FUN_00408bf0(&local_90,iVar3,0); // some operation
        uVar5 = 0;
        uVar4 = FUN_006fbc40(0,0);
        FUN_007f96a0(0x764e740,0,uVar4,uVar5); // play sound with ID 0x764e740
        FUN_006fbc70();
        FUN_006ad490(); // cleanup
        return 1;
    case 9: // actionType == 0x1B
        iVar3 = FUN_0073e090(); // get object
        if (iVar3 != 0) {
            (**(code **)(*thisPtr + 0x2c))(iVar3,1,0,0,0x3f800000,0x3f800000); // vtable call
        }
        uVar5 = 0;
        uVar4 = FUN_006fbc40(0,0);
        FUN_007f96a0(0xef894a5b,0,uVar4,uVar5); // play sound
        FUN_006fbc70();
        return 1;
    case 10: // actionType == 0x1C
        iVar3 = FUN_006252f0(); // get something
        (**(code **)(*(int *)thisPtr[0x17] + 0x290))(iVar3 != 0,1); // vtable call with bool
        return 1;
    case 0xb: // actionType == 0x1D
        uVar5 = 0;
        uVar4 = FUN_006fbc40(0,0);
        FUN_007f96a0(0,0,uVar4,uVar5); // play sound with ID 0
        FUN_006fbc70();
        *(uint *)(thisPtr[0x17] + 0x1b94) |= 0x2000; // set flag
        return 1;
    case 0xc: // actionType == 0x1E
        if (*(int *)(thisPtr[0x17] + 0x1e70) == 0) {
            iVar3 = FUN_0073e0c0(); // get something
            if (iVar3 == 0) goto LAB_0073eaae;
        }
        else {
            iVar3 = -0x13d7b096; // negative constant
        }
        (**(code **)(*thisPtr + 0x2c))(iVar3,1,0,0,0x3f800000,0x3f800000);
LAB_0073eaae:
        uVar5 = 0;
        uVar4 = FUN_006fbc40(0,0);
        FUN_007f96a0(0xf0a79e11,0,uVar4,uVar5);
        FUN_006fbc70();
        return 1;
    case 0xd: // actionType == 0x1F
        iVar3 = FUN_006e6410(); // get object
        if (iVar3 != 0) {
            FUN_00470230(iVar3, param_3 * DAT_00d636b8, 0); // some operation with scaled distance
            return 1;
        }
        break;
    case 0xe: // actionType == 0x20
        iVar3 = *thisPtr;
        uVar4 = FUN_006252f0(); // get something
        (**(code **)(iVar3 + 0x30))(uVar4); // vtable call offset 0x30
        return 1;
    case 0xf: // actionType == 0x21
        uVar8 = 0;
        uVar4 = FUN_006fbc40(0,0);
        uVar7 = 0;
        uVar5 = FUN_006252f0(0,uVar4,uVar8); // get something with sound handle
        FUN_007f96a0(uVar5,uVar7,uVar4,uVar8); // play sound
        FUN_006fbc70();
        return 1;
    case 0x10: // actionType == 0x22
        FUN_00719e70(); // handle exit/cleanup?
        return 1;
    default:
        retVal = FUN_0080e8e0(param_2, param_3, param_4, actionType, param_6);
    }
    return retVal;
}