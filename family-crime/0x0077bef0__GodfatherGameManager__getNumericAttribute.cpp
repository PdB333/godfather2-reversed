// FUNC_NAME: GodfatherGameManager::getNumericAttribute
float GodfatherGameManager::getNumericAttribute(int attributeId, int* param_2)
{
    float fVar1;
    char cVar2;
    int iVar3;
    int iVar4;
    int* piVar5;
    int iVar6;
    float10 fVar7;
    float10 fVar8;
    float local_10;
    undefined8 local_c;
    undefined4 local_4;

    fVar1 = DAT_01205228; // current game time
    piVar5 = (int*)*param_2; // dereference param_2 to get object pointer
    local_10 = 0.0;
    switch(attributeId) {
    case 0: // health ratio
        fVar8 = (float10)(**(code **)(*piVar5 + 0xc0))(); // get current health
        fVar7 = (float10)(**(code **)(*piVar5 + 0xc4))(); // get max health
        return (float10)(float)fVar8 / fVar7;
    case 2: // distance to player
        if ((piVar5 != (int *)0x0) && (iVar3 = FUN_00711680(), iVar3 != 0)) { // is player valid?
            piVar5 = (int *)FUN_00722220(); // get player object
            if (piVar5 != (int *)0x0) {
                if (*piVar5 == 0) break;
                iVar3 = *piVar5 + -0x48;
            }
            if (iVar3 != 0) {
                iVar3 = FUN_00471610(); // get position
                iVar4 = FUN_00471610(); // get position
                fVar8 = (float10)FUN_0045c4b0(iVar4 + 0x30,iVar3 + 0x30); // calculate distance
                return fVar8;
            }
        }
        break;
    case 3: // attribute 3
        if (piVar5 == (int *)0x0) break;
        iVar3 = FUN_00711680();
        goto LAB_0077bf6a;
    case 4: // attribute 4 - some integer with sign handling
        if ((piVar5 != (int *)0x0) && (iVar3 = FUN_007175b0(), iVar3 != 0)) {
            iVar3 = FUN_007013c0();
            if (-1 < iVar3) {
                return (float10)iVar3;
            }
            return (float10)iVar3 + (float10)DAT_00e44578; // handle negative as unsigned
        }
        break;
    case 5: // attribute 5 - integer from +0x328
        if ((piVar5 != (int *)0x0) && (iVar3 = FUN_007175b0(), iVar3 != 0)) {
            if (-1 < *(int *)(iVar3 + 0x328)) {
                return (float10)*(int *)(iVar3 + 0x328);
            }
            return (float10)*(int *)(iVar3 + 0x328) + (float10)DAT_00e44578;
        }
        break;
    case 0xd: // attribute 13 - float from +0x34c
        if ((piVar5 != (int *)0x0) && (iVar3 = FUN_007175b0(), iVar3 != 0)) {
            local_10 = *(float *)(iVar3 + 0x34c);
        }
        break;
    case 0x13: // attribute 19
        if (piVar5 != (int *)0x0) {
            fVar8 = (float10)FUN_0071ad50();
            return fVar8;
        }
        break;
    case 0x18: // attribute 24 - time since last event
        if (piVar5 != (int *)0x0) {
            return (float10)(DAT_01205228 - (float)piVar5[0x883]); // current time - last event time
        }
        break;
    case 0x19: // attribute 25 - time since last something
        local_10 = DAT_00d5f6f0; // default value
        if ((piVar5 != (int *)0x0) && (iVar3 = FUN_00717700(), iVar3 != 0)) {
            return (float10)(fVar1 - *(float *)(iVar3 + 0x28));
        }
        break;
    case 0x1c: // attribute 28
        if (piVar5 != (int *)0x0) {
            fVar8 = (float10)FUN_0077bcb0();
            return fVar8;
        }
        break;
    case 0x20: // attribute 32 - time until next event
        if (piVar5 != (int *)0x0) {
            fVar1 = (float)piVar5[0x92f]; // interval
            if (piVar5[0x92f] < 0) {
                fVar1 = fVar1 + DAT_00e44578;
            }
            if (fVar1 * DAT_00d5efb8 <= (float)piVar5[0x883]) { // if interval * multiplier <= last event time
                return (float10)(DAT_01205228 - (float)piVar5[0x883]); // time since last event
            }
            return (float10)(DAT_01205228 - fVar1 * DAT_00d5efb8); // time until next event
        }
        break;
    case 0x25: // attribute 37 - integer from +0x935
        if (piVar5 != (int *)0x0) {
            if (-1 < piVar5[0x935]) {
                return (float10)piVar5[0x935];
            }
            return (float10)piVar5[0x935] + (float10)DAT_00e44578;
        }
        break;
    case 0x26: // attribute 38
        local_10 = DAT_00d5f6f0;
        if ((param_2[1] != 0) && (piVar5 != (int *)0x0)) {
            fVar8 = (float10)FUN_0077dbd0(param_2[1]);
            return fVar8;
        }
        break;
    case 0x27: // attribute 39
        local_10 = DAT_00d5f6f0;
        if ((param_2[1] != 0) && (piVar5 != (int *)0x0)) {
            fVar8 = (float10)FUN_0077db70(param_2[1]);
            return fVar8;
        }
        break;
    case 0x2d: // attribute 45
        local_10 = DAT_00d5f6f0;
        if (piVar5 != (int *)0x0) {
            fVar8 = (float10)FUN_007192d0();
            return fVar8;
        }
        break;
    case 0x32: // attribute 50 - time since something at +0x942
        local_10 = DAT_00e44758;
        if (piVar5 != (int *)0x0) {
            return (float10)(DAT_01205228 - (float)piVar5[0x942]);
        }
        break;
    case 0x33: // attribute 51 - time since something at +0x947
        local_10 = DAT_00d5f6f0;
        if (piVar5 != (int *)0x0) {
            return (float10)(DAT_01205228 - (float)piVar5[0x947]);
        }
        break;
    case 0x35: // attribute 53 - distance to something
        local_10 = 0.0;
        iVar3 = FUN_00746ba0(piVar5);
        if ((iVar3 != 0) && (cVar2 = FUN_00711210(), cVar2 != '\0')) {
            iVar4 = FUN_00471610();
            fVar8 = (float10)FUN_0045c4b0(iVar3 + 0x18,iVar4 + 0x30);
            return fVar8;
        }
        break;
    case 0x36: // attribute 54 - float from +0x24
        local_10 = DAT_00d5f6f0;
        iVar3 = FUN_00746ba0(piVar5);
        if ((iVar3 != 0) && (cVar2 = FUN_00711210(), cVar2 != '\0')) {
            return (float10)*(float *)(iVar3 + 0x24);
        }
        break;
    case 0x38: // attribute 56 - time since something at +0x958
        local_10 = DAT_00d5f6f0;
        if (piVar5 != (int *)0x0) {
            return (float10)(DAT_01205228 - (float)piVar5[0x958]);
        }
        break;
    case 0x39: // attribute 57 - time since something
        local_10 = DAT_00d5f6f0;
        if ((piVar5 != (int *)0x0) && (iVar3 = FUN_00717700(), iVar3 != 0)) {
            return (float10)(fVar1 - *(float *)(iVar3 + 0x1c));
        }
        break;
    case 0x3a: // attribute 58 - time since something at +0x884
        if (piVar5 != (int *)0x0) {
            return (float10)(DAT_01205228 - (float)piVar5[0x884]);
        }
        break;
    case 0x3c: // attribute 60 - distance to something
        local_10 = DAT_00d5f6f0;
        if (piVar5 != (int *)0x0) {
            iVar6 = FUN_006e6410();
            iVar3 = piVar5[0x877]; // some object pointer
            iVar4 = piVar5[0x87b]; // another object pointer
            if (((iVar3 != 0) || (iVar4 != 0)) && (iVar6 != 0)) {
                if (iVar3 == 0) {
                    local_4 = *(undefined4 *)(iVar4 + 0x4c);
                    local_c = *(undefined8 *)(iVar4 + 0x44);
                }
                else {
                    local_4 = *(undefined4 *)(iVar3 + 0x4c);
                    local_c = *(undefined8 *)(iVar3 + 0x44);
                }
                iVar3 = FUN_00471610();
                fVar8 = (float10)FUN_0045c4b0(iVar3 + 0x30,&local_c);
                return fVar8;
            }
        }
        break;
    case 0x4a: // attribute 74 - distance to something
        if (((piVar5 == (int *)0x0) || (iVar3 = FUN_0077bea0(piVar5), iVar3 == 0)) ||
           (iVar3 = FUN_007631c0(), iVar3 == 0)) break;
        iVar3 = FUN_00471610();
        FUN_007631c0();
        goto LAB_0077bf80;
    case 100: // attribute 100
        local_10 = DAT_00d5f6f0;
        if (piVar5 == (int *)0x0) break;
        iVar3 = FUN_007821b0(piVar5);
        goto LAB_0077bf6a;
    case 0x65: // attribute 101
        local_10 = DAT_00d5f6f0;
        if ((piVar5 == (int *)0x0) || (**(int **)(DAT_012233a0 + 4) == 0)) break;
        iVar3 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
LAB_0077bf6a:
        if (iVar3 != 0) {
            iVar3 = FUN_00471610();
LAB_0077bf80:
            iVar4 = FUN_00471610();
            fVar8 = (float10)FUN_0045c4b0(iVar4 + 0x30,iVar3 + 0x30);
            return fVar8;
        }
    }
    return (float10)local_10;
}