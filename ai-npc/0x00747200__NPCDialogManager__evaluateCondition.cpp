// FUNC_NAME: NPCDialogManager::evaluateCondition
int __thiscall NPCDialogManager::evaluateCondition(int thisPtr, undefined4 arg2, undefined4 arg3, int queryType, undefined4 arg5)
{
    byte subFlag;
    uint3 highByte;
    int result;

    highByte = (uint3)((uint)(queryType - 10) >> 8);
    switch (queryType - 10)
    {
    case 0: // Check if a sub-object flag indicates "available"
        subFlag = *(byte *)(*(int *)(thisPtr + 0x54) + 0x2c); // this->m_pSubObj->flag
        if (((subFlag & 1) != 0) && (-1 < (char)subFlag)) // flag bit 0 set and non-negative
        {
            return 0; // condition false
        }
        return 1; // condition true

    case 1: // Get a value from global system
        result = getPlayerManager();
        result = getSomeValue(result + 0x30);
        return result;

    case 2: // Check if both pointers are non-null
        if ((*(int *)(thisPtr + 0x5c) == 0) || (*(int *)(thisPtr + 100) == 0)) // this->m_pPtrA or this->m_pPtrB
        {
            goto fallbackReturnZero;
        }
        break; // fall through to return 1

    case 3: // Check if either pointer is null
        if ((*(int *)(thisPtr + 0x5c) != 0) && (*(int *)(thisPtr + 100) != 0))
        {
            return (uint)highByte << 8; // 0
        }
        return CONCAT31(highByte, 1); // 1

    case 4: // Check if count exceeds 9
        return CONCAT31(highByte, 9 < *(uint *)(thisPtr + 0x58)); // this->m_iCount > 9

    case 5: // Check if a float is below threshold
        if (*(float *)(thisPtr + 0x30) < _DAT_00d5780c) // this->m_fValue < globalThreshold
        {
            goto fallbackReturnZero;
        }
        break;

    default: // Pass to base condition handler
        result = FUN_004ac640(arg2, arg3, queryType, arg5);
        return result;
    }

    return CONCAT31(highByte, 1);

fallbackReturnZero:
    return (uint)highByte << 8;
}