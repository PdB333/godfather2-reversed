// FUNC_NAME: PlayerSM::processEvent

/* 0x00886700 - Player State Machine event handler
 * Handles events 10-23 (switch param_5 - 10)
 * Stores state flags at +0x1c, character pointer at +0x16, subcontroller at +0x14
 */
unsigned char __thiscall PlayerSM::processEvent(
    int* thisPtr,
    uint eventParam2,          // param_2
    uint eventParam3,          // param_3
    uint eventParam4,          // param_4
    int  eventId,              // param_5
    uint eventParam6)          // param_6
{
    float fVar1;
    char cVar2;
    int iVar4;
    uint uVar5;
    int* piVar6;
    float10 fVar7;
    uint uVar8;
    int localPosX;             // local_20
    int localPosY;             // local_1c
    uint localParamB;          // local_18
    uint localParamA;          // local_14

    unsigned char result = 1;

    switch (eventId - 10)
    {
    case 0:  // eventId=10
        /* Probably starts a new action/animation */
        sub_8853f0_playAnimation();
        return 1;

    case 1:  // eventId=11
        /* Plays a sound effect */
        sub_886310_playSound();
        return 1;

    case 2:  // eventId=12
        /* Checks if some global distance threshold is exceeded */
        if (_DAT_00d577a0 < (float)thisPtr[0xc])  // +0x0C: some distance/speed
        {
            // Clear bit ~0x08000000 at address (thisPtr[0x16] + 0x1b94)
            *(uint*)(thisPtr[0x16] + 0x1b94) &= 0xf7ffffff;
            return 1;
        }
        break;

    case 3:  // eventId=13
        sub_885790_startCollision();
        return 1;

    case 4:  // eventId=14
        sub_885e10_finishAction();
        return 1;

    case 6:  // eventId=16
        /* Sets flag 0x10 and calls sub on character +0x3C */
        thisPtr[0x1c] |= 0x10;                     // +0x1C: flags
        sub_4088c0(thisPtr[0x16] + 0x3c);           // character +0x3C (some timer?)
        return 1;

    case 7:  // eventId=17
        sub_885630_resetAction();
        return 1;

    case 8:  // eventId=18
        sub_7f63e0(0x50);                          // presumably allocate object
        if (thisPtr[0x14] == 0)                    // sub-controller null?
            return 1;
        if (thisPtr[0x14] == 0x48)                 // sub-controller at offset?
            return 1;

        cVar2 = sub_543050_isCharacterBusy(thisPtr[0x16]);  // character +0x16
        if (cVar2 == 0)
        {
            fVar7 = (float10)sub_6b6f70_random();   // get random
            thisPtr[0x1b] = (int)(float)(fVar7 * (float10)_DAT_00d5c458);  // multiply by global
        }

        /* Check if something forces the action */
        if ((((*(byte*)(thisPtr + 0x1c) & 1) != 0) ||         // flag 0x01 set
             ((int*)thisPtr[0x16] == (int*)0x0)) ||            // character missing
            (cVar2 = (**(code**)(*(int*)thisPtr[0x16] + 0x1bc))(), cVar2 != 0))  // vtable call at +0x1BC
        {
            // Derive sub-controller (offset -0x48)
            int* subCtl;
            if (thisPtr[0x14] == 0)
                subCtl = 0;
            else
                subCtl = (int*)(thisPtr[0x14] - 0x48);

            if (*(int*)(subCtl + 0xb74) != 0 || *(int*)(subCtl + 0xb78) != 0)
            {
                thisPtr[0x1c] |= 2;  // set flag 0x02
            }
        }

LAB_0088685b:
        localParamA = 0;
        localParamB = 0;

        int* subCtl;
        if (thisPtr[0x14] == 0)
            subCtl = 0;
        else
            subCtl = (int*)(thisPtr[0x14] - 0x48);

        cVar2 = (**(code**)(*subCtl + 0x1f8))(thisPtr[0x16], &localParamB);  // vtable call
        if (cVar2 == 0)
            return 1;

        cVar2 = sub_8754b0_checkPath(&localPosX);  // localPosX = stack
        if (cVar2 == 0)
            return 1;

        goto LAB_008868b6;

    case 9:  // eventId=19
        localPosX = thisPtr[0x17];   // +0x17: position x (or some coordinate)
        localPosY = thisPtr[0x18];   // +0x18: position y

        if ((thisPtr[0x1c] >> 7) & 1)   // bit 7 of flags
        {
            localPosX = thisPtr[0x19];   // +0x19: alternative x
            localPosY = thisPtr[0x1a];   // +0x1a: alternative y
        }

        localParamA = 0;
        localParamB = 0;

        int* subCtl;
        if (thisPtr[0x14] == 0)
            subCtl = 0;
        else
            subCtl = (int*)(thisPtr[0x14] - 0x48);

        (**(code**)(*subCtl + 0x1f8))(thisPtr[0x16], &localParamB);  // vtable call

        fVar7 = (float10)sub_884df0_getTimeStep();  // get time delta

        cVar2 = sub_8754b0_checkPath(&localPosX);
        if ((cVar2 == 0) || (cVar2 = sub_8754b0_checkPath(&stack0xffffffd8), cVar2 != 0))
        {
            cVar2 = sub_8754b0_checkPath(&localPosX);
            if ((cVar2 == 0) && (cVar2 = sub_8754b0_checkPath(&stack0xffffffd8), cVar2 != 0))
            {
                iVar4 = thisPtr[0x16];
                uVar5 = 0xad385595;  // some hash
                goto LAB_008869d1;
            }
        }
        else
        {
            if (thisPtr[0x14] == 0)
            {
                iVar4 = thisPtr[0x16];
                uVar5 = 0x488999ae;  // another hash
            }
            else
            {
                iVar4 = thisPtr[0x16];
                uVar5 = 0x488999ae;
            }
LAB_008869d1:
            uVar5 = sub_875af0_getAnimationId(iVar4, uVar5);  // resolve animation
            (**(code**)(*thisPtr + 0x2c))(uVar5, 0, 1, 0, (float)fVar7, 0x3f800000);
            sub_8852d0_playAnimation();
            thisPtr[0x1c] |= 0x400;  // set flag 0x400
        }

        cVar2 = sub_8754b0_checkPath(&stack0xffffffd8);
        if (cVar2 == 0)
        {
            thisPtr[0x1c] &= ~0x40;  // clear flag 0x40
            return 1;
        }

LAB_008868b6:
        thisPtr[0x1c] |= 0x40;      // set flag 0x40
        return 1;

    case 10: // eventId=20
        sub_886000_resetState();
        return 1;

    case 11: // eventId=21
        fVar1 = (float)thisPtr[0xc];  // distance?
        fVar7 = (float10)sub_45fa90_getTimeScale();
        sub_884d00_interpolate(thisPtr + 0x30, thisPtr + 0x38, (float)((float10)fVar1 / fVar7));
        return 1;

    case 12: // eventId=22
        (**(code**)(*(int*)thisPtr[0x16] + 0x7c))();  // vtable call on character
        thisPtr[0x1c] &= ~0x4;   // clear flag 0x04
        return 1;

    case 13: // eventId=23
        if ((((*(byte*)(thisPtr + 0x1c) & 1) == 0) &&   // flag 0x01 not set
             (thisPtr[0x14] != 0)) &&                     // sub-controller exists
            (thisPtr[0x14] != 0x48))
        {
            int* subCtl;
            if (thisPtr[0x14] == 0)
                subCtl = 0;
            else
                subCtl = (int*)(thisPtr[0x14] - 0x48);

            if ((*(byte*)(subCtl + 0xc8a) & 1) != 0)   // check some byte flag
            {
                uVar8 = 0;
                uVar5 = sub_6fbc40_getObject(0, 0);     // get some object
                sub_7f96a0_playSound(0xb90c41d7, 0, uVar5, uVar8);
                sub_6fbc70_releaseObject();
                return 1;
            }
        }
        break;

    default:
        // Base class handler
        result = sub_4ac700_baseHandler(eventParam2, eventParam3, eventParam4, eventId, eventParam6);
        break;
    }
    return result;
}