// FUNC_NAME: Character::executeAction
undefined __thiscall Character::executeAction(int thisPtr, int actionIndex, int targetID, char param3, undefined4 param4, byte param5, undefined4 param6, undefined4 param7, undefined4 param8, undefined4 param9, undefined4 param10)
{
    float fVar1;
    int iVar2;
    float fVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    float fVar7;
    float fVar8;
    byte bLocal65 = 0;
    undefined4 local_60 = 0;
    undefined4 local_5c;
    undefined4 local_58;
    undefined4 local_54;
    int local_34;
    undefined4 local_2c;
    undefined4 *local_20;

    // in_EAX is the this pointer (ECX) in __thiscall
    if (thisPtr == 0 || actionIndex < 0)
        return 0;

    // Dereference linked list: this->actionList at offset 0x124
    iVar6 = *(int *)(thisPtr + 0x124); // +0x124: head of action list

    iVar4 = 0;
    if (actionIndex > 0)
    {
        do
        {
            iVar6 = *(int *)(iVar6 + 0x124); // each node has next pointer at +0x124
            if (iVar6 == 0)
                return 0;
            iVar4 = iVar4 + 1;
        } while (iVar4 < actionIndex);
    }

    if (iVar6 == 0)
        return 0;

    if (targetID != -1)
    {
        bLocal65 = 1;

        if (*(int *)(iVar6 + 0x10c) != 0) // +0x10c: animation handle or pointer
        {
            setAnimation(*(int *)(iVar6 + 0x10c), iVar6, param6); // FUN_005826b0
        }

        local_60 = 0;
        local_54 = param10;
        local_5c = param8;
        local_58 = param9;
        startAnimation(); // FUN_00586970 - maybe starts the animation
        iVar4 = *(int *)(iVar6 + 0x14); // +0x14: some state variable
        local_20 = &local_60;
        local_34 = targetID;
        local_2c = param7;
        configureActionState(); // FUN_00578770

        // Clear bit 7 (0x80) in flags at +0x10
        *(uint *)(iVar6 + 0x10) = *(uint *)(iVar6 + 0x10) & 0xffffff7f;
        // Set some attribute at +0x120
        *(byte *)(iVar6 + 0x120) = param5;

        fVar8 = DAT_00e2b1a4; // Unknown global constant

        if (param3 != '\0')
        {
            iVar2 = *(int *)(iVar6 + 0x110); // +0x110: some duration/velocity
            fVar1 = *(float *)(iVar6 + 0x114); // +0x114: another float (maybe speed)
            *(undefined4 *)(iVar6 + 0x110) = 1; // set to 1 (active?)
            *(byte *)(iVar6 + 0x121) = 0; // +0x121: flag reset
            fVar3 = DAT_00e2cb90;

            if (*(int *)(iVar6 + 0x2f0) == 0) // +0x2f0: some pointer (maybe parent/other)
            {
                fVar7 = ((*(float *)(iVar6 + 0x24) - fVar8) / _DAT_011260b0) * DAT_00e35654;
                *(float *)(iVar6 + 0x118) = fVar7; // +0x118: computed value
                if (fVar3 < fVar7)
                {
                    *(float *)(iVar6 + 0x118) = fVar3;
                }
                *(undefined4 *)(iVar6 + 0x11c) = 0; // +0x11c: another value
            }
            else
            {
                iVar5 = getParentData(); // FUN_00571d70
                fVar8 = DAT_00e2b1a4;
                *(float *)(iVar6 + 0x118) = *(float *)(iVar5 + 4) / _DAT_011260b0;
                *(undefined4 *)(iVar6 + 0x11c) = *(undefined4 *)(iVar5 + 0xc);
            }

            if (iVar2 != 0)
            {
                if (iVar2 < 0)
                {
                    fVar8 = (fVar8 - fVar1 * _DAT_00e446b8) * *(float *)(iVar6 + 0x118);
                    *(float *)(iVar6 + 0x114) = fVar8;
                    if (fVar8 < 0.0)
                    {
                        // Clear bits 0,1,30 (and set something?) in flags
                        *(uint *)(iVar6 + 0x10) = *(uint *)(iVar6 + 0x10) & 0xedfffffe;
                        *(undefined4 *)(iVar6 + 0x114) = 0;
                        return 1;
                    }
                    goto LAB_00572344;
                }
LAB_00572397:
                *(uint *)(iVar6 + 0x10) = *(uint *)(iVar6 + 0x10) & 0xedfffffe;
                *(undefined4 *)(iVar6 + 0x114) = 0;
                return 1;
            }
            if (iVar4 == -1)
                goto LAB_00572397;
        }
        *(undefined4 *)(iVar6 + 0x110) = 0; // reset duration
    }

LAB_00572344:
    *(uint *)(iVar6 + 0x10) = *(uint *)(iVar6 + 0x10) & 0xedfffffe;
    return bLocal65;
}