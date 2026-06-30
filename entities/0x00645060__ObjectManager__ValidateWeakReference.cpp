// FUNC_NAME: ObjectManager::ValidateWeakReference
int ObjectManager::ValidateWeakReference(int* pObjectRef)
{
    CRITICAL_SECTION* pCS = *(CRITICAL_SECTION**)((int)this + 0x4e8);
    if (pCS != nullptr)
    {
        EnterCriticalSection(pCS);
    }

    int result = FUN_00644d30(pObjectRef);
    if ((result == 0) && ((pObjectRef[1] & 2) == 0))
    {
        uint offsetBits = pObjectRef[1] & 0x7ffffff8;           // +0x4 low bits = flags, rest = relative offset
        int* pTarget = (int*)((int)pObjectRef + offsetBits);    // iVar1

        uint flagValue = (~(*(byte*)((int)pTarget + 4)) & 1);   // complement of low bit at target[+4]

        if ((pObjectRef[1] & 1) == 0)                           // if not a weak reference flag
        {
            int* pDiff = (int*)((int)pObjectRef +
                ((*(uint*)((int)pObjectRef + (4 - pObjectRef[0])) & 0x7ffffff8) - pObjectRef[0]));
            if (pDiff != pObjectRef)
            {
                flagValue++;
            }
        }

        result = FUN_00644d30(pTarget);
        result = flagValue + result;

        if ((result == 0) && (pTarget == *(int**)((int)this + 0x440)))
        {
            uint sizeCheck = (*(uint*)((int)pTarget + 4) & 0x7ffffff8) < 0x10;
            uint lowBitCheck = (~(*(byte*)((int)pTarget + 4)) & 1);
            result = sizeCheck + lowBitCheck;
        }
    }

    if (pCS != nullptr)
    {
        LeaveCriticalSection(pCS);
    }

    return result;
}