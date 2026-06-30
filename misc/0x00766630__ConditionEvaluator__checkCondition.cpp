// FUNC_NAME: ConditionEvaluator::checkCondition
// Address: 0x00766630
// The function checks various condition types (ID 0x0B to 0x13) for state machine transitions.
// It uses a switch on the conditionID minus 11 (0x0B). Default falls through to base class handler.

bool __thiscall ConditionEvaluator::checkCondition(int conditionID, int arg2, int arg3, int arg5)
{
    char cVar1;
    int iVar3;
    int iVar4;
    int *piVar5;
    float fVar6, fVar7, fVar8;
    float timerValue;
    float distanceSq;
    float10 extraout_ST0, extraout_ST0_00;

    switch (conditionID - 0x0B)
    {
    case 0: // conditionID == 11: Timer threshold check
        timerValue = getGlobalTimerValue(); // FUN_0040aa10
        if (timerValue >= 1.0f)
            return true;
        break;

    case 1: // conditionID == 12: State and ability check
        if ((*(int *)(this + 0x54) != 0) && (*(int *)(this + 0x54) != 0x48) &&
            (cVar1 = hasAbility(8), cVar1 != '\0'))  // FUN_00690210(8)
            return true;
        break;

    case 2: // conditionID == 13: State, ability, and flag bit 0 check
        if ((((*(int *)(this + 0x54) != 0) && (*(int *)(this + 0x54) != 0x48)) &&
            (cVar1 = hasAbility(8), cVar1 != '\0')) && ((*(byte *)(this + 0x60) & 1) == 0))
            return true;
        break;

    case 3: // conditionID == 14: Specific sub-object state check
        iVar3 = *(int *)(*(int *)(this + 0x50) + 0x1C78); // owner->field_0x1C78
        if (iVar3 == 0)
            return true;
        return iVar3 == 0x48;

    case 4: // conditionID == 15: Sub-object status flags/state
        if ((((*(uint *)(*(int *)(this + 0x50) + 0x1B94) >> 1 & 1) != 0) ||
             (cVar1 = *(char *)(*(int *)(this + 0x50) + 0x1B8C), cVar1 == '\x01')) ||
            ((cVar1 == '\x02' || (cVar1 == '\x03'))))
            return true;
        break;

    case 5: // conditionID == 16: Distance check between local and target
        iVar3 = getLocalPlayerTransform();   // FUN_00471610 (first call)
        iVar4 = getTargetPlayerTransform();  // FUN_00471610 (second call, likely different object)
        fVar6 = *(float *)(iVar4 + 0x30) - *(float *)(iVar3 + 0x30); // X difference
        fVar7 = *(float *)(iVar4 + 0x34) - *(float *)(iVar3 + 0x34); // Y difference
        fVar8 = *(float *)(iVar4 + 0x38) - *(float *)(iVar3 + 0x38); // Z difference
        getDistanceSquared(); // FUN_007ff880 (possibly modifies internal state or returns distance)
        distanceSq = fVar8 * fVar8 + fVar7 * fVar7 + fVar6 * fVar6;
        if (distanceSq <= g_maxEngagementDistance) // DAT_00d65848
            return true;
        break;

    case 6: // conditionID == 17: Context object and ability check
        iVar3 = getContextObject(); // FUN_007ff880
        if ((iVar3 != 0) && (cVar1 = checkAbilityFlag(4), cVar1 != '\0')) // FUN_00690150(4)
            return true;
        break;

    case 7: // conditionID == 18: Context object flag and virtual method threshold
        piVar5 = (int *)getContextObject();
        if (((piVar5 != 0) && (((uint)piVar5[0x322] >> 3 & 1) == 0)) &&
            ((**(code **)(*piVar5 + 0x1B0))(), g_globalThreshold > extraout_ST0_00)) // DAT_00d6584c
            return true;
        break;

    case 8: // conditionID == 19: Multi-state and flag check
        if (*(int *)(this + 0x54) == 0)
            return false;
        if (*(int *)(this + 0x54) == 0x48)
            return false;
        iVar3 = getContextObject();
        if ((iVar3 != 0) && ((*(byte *)(this + 0x60) & 4) == 0))
            return true;
        iVar3 = getContextObject();
        if (iVar3 != 0)
            return false;
        if ((*(byte *)(this + 0x60) & 4) == 0)
            return false;
        return true;

    default:
        // Base class handler for unknown condition IDs
        return baseClassCheckCondition(arg2, arg3, conditionID, arg5); // FUN_004ac640
    }
    return false;
}