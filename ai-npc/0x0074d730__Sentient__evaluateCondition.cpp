// FUNC_NAME: Sentient::evaluateCondition
// Address: 0x0074d730
// This function evaluates a condition identified by conditionId (param_4) and returns true/false.
// It checks various state fields on the Sentient object (this) and its components.
// Offsets: +0x8c = pointer to component A (maybe action component), +0x94 = pointer to component B,
//          +0xe4 = flags (bitfield), +0x20 = pointer to parent/vehicle, +0x30 = float (e.g., health/charge),
//          +0x88 = pointer to another object with field at +0x1e70.

bool Sentient::evaluateCondition(int conditionId, int arg2, int arg3, void* dataPtr)
{
    char boolResult;
    int componentA; // pointer at this+0x8c
    int componentB; // pointer at this+0x94
    int temp;
    int playerObj;

    switch (conditionId - 10)
    {
    case 0: // Condition 10
        if (*(int*)(this + 0x8c) != 0)
            return *(int*)(this + 0x8c) == 0x48;
        return true;

    case 1: // Condition 11
        return *(int*)(this + 0x94) == 0;

    case 2: // Condition 12
        if ((*(int*)(this + 0x8c) == 0 || *(int*)(this + 0x8c) == 0x48) &&
            *(int*)(this + 0x94) == 0)
            return true;
        break;

    case 3: // Condition 13
        if (*(int*)(this + 0x94) == 0)
            return false;
        boolResult = FUN_0074c4e0(*(int*)(this + 0x94) + 0x44); // check flag at componentB+0x44
        return (bool)boolResult;

    case 4: // Condition 14
        if (*(int*)(this + 0x8c) == 0)
            return false;
        if (*(int*)(this + 0x8c) == 0x48)
            return false;
        temp = (*(int*)(this + 0x8c) == 0) ? 0 : *(int*)(this + 0x8c) - 0x48;
        boolResult = FUN_0074c4e0(temp + 0x6c); // check flag at (componentA - 0x48) + 0x6c
        if (boolResult == '\0')
            return false;
        return true;

    case 5: // Condition 15
        if (*(int*)(this + 0x8c) != 0)
            return *(int*)(this + 0x8c) != 0x48;
        return false;

    case 6: // Condition 16
        if ((*(uint*)(this + 0xe4) >> 4 & 1) == 0)
            return false;
        return true;

    case 7: // Condition 17
        return *(int*)(this + 0x94) != 0;

    case 8: // Condition 18
        if (*(int*)(this + 0x8c) != 0 && *(int*)(this + 0x8c) != 0x48)
        {
            temp = (*(int*)(this + 0x8c) == 0) ? 0 : *(int*)(this + 0x8c) - 0x48;
            boolResult = FUN_0074c4e0(temp + 0x6c);
            if (boolResult != '\0')
            {
                temp = (*(int*)(this + 0x8c) == 0) ? 0 : *(int*)(this + 0x8c) - 0x48;
                if (*(int*)(temp + 0x94) == 1)
                    return true;
            }
        }
        break;

    case 9: // Condition 19
        if (*(int*)(this + 0x8c) == 0)
            return false;
        if (*(int*)(this + 0x8c) == 0x48)
            return false;
        temp = (*(int*)(this + 0x8c) == 0) ? 0 : *(int*)(this + 0x8c) - 0x48;
        boolResult = FUN_0074c4e0(temp + 0x6c);
        if (boolResult == '\0')
            return false;
        goto LAB_0074d943;

    case 10: // Condition 20
        if (*(int*)(this + 0x20) == 0 &&
            *(int*)(this + 0x8c) != 0 && *(int*)(this + 0x8c) != 0x48)
        {
            temp = (*(int*)(this + 0x8c) == 0) ? 0 : *(int*)(this + 0x8c) - 0x48;
            boolResult = FUN_0074c4e0(temp + 0x6c);
            if (boolResult != '\0' && FUN_0074c060() != '\0')
                return true;
        }
        break;

    case 11: // Condition 21
        boolResult = FUN_004ac260();
        if (boolResult == '\0')
            return false;
        goto LAB_0074d91b;

    case 12: // Condition 22
        if (*(int*)(this + 0x8c) != 0 && *(int*)(this + 0x8c) != 0x48 &&
            *(int*)(this + 0x94) != 0)
            return true;
        break;

    case 13: // Condition 23
        playerObj = FUN_00471610();
        temp = FUN_00721d70(4, playerObj + 0x30, DAT_00e51920, 0);
        if (temp != 0)
            return false;
        boolResult = FUN_0074d690(DAT_00d64704, _DAT_00e51938);
        return boolResult == '\0';

    default: // Conditions not handled above
        boolResult = FUN_004ac640(arg2, arg3, conditionId, dataPtr);
        return (bool)boolResult;

    case 15: // Condition 25
        if (*(int*)(this + 0x20) != 0)
            return false;
LAB_0074d91b:
        if (*(int*)(this + 0x8c) != 0 && *(int*)(this + 0x8c) != 0x48)
        {
LAB_0074d943:
            boolResult = FUN_0074c0b0();
            if (boolResult != '\0')
                return true;
        }
        break;

    case 16: // Condition 26
        return (bool)((*(uint*)(this + 0xe4) >> 1) & 1);

    case 17: // Condition 27
        return (bool)(~((*(uint*)(this + 0xe4) >> 1) & 1) & 1);

    case 18: // Condition 28
        if ((*(uint*)(this + 0xe4) >> 9 & 1) == 0 ||
            _DAT_00d6476c < *(float*)(this + 0x30))
        {
            playerObj = FUN_00471610();
            temp = FUN_00721d70(4, playerObj + 0x30, DAT_00e51920, 0);
            if (temp != 0)
                return true;
        }
        return false;

    case 19: // Condition 29
        boolResult = FUN_005fd740();
        return boolResult == '\0';

    case 20: // Condition 30
        if ((*(uint*)(this + 0xe4) >> 1 & 1) != 0 && *(int*)(this + 0x20) == 0)
            return true;
        break;

    case 21: // Condition 31
        if ((*(uint*)(this + 0xe4) >> 1 & 1) != 0 &&
            FUN_004abe10(0x20) != '\0')
            return true;
        break;

    case 22: // Condition 32
        if ((*(uint*)(this + 0xe4) >> 1 & 1) == 0)
            return false;
        if (*(float*)((int)dataPtr + 4) <= *(float*)(this + 0x30) &&
            *(float*)(this + 0x30) != *(float*)((int)dataPtr + 4))
            return true;
        break;

    case 23: // Condition 33
        if ((*(uint*)(this + 0xe4) >> 3 & 1) != 0 &&
            *(int*)(*(int*)(this + 0x88) + 0x1E70) == 0)
            return true;
        break;
    }

    return false;
}