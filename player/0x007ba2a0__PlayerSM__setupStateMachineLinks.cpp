// FUNC_NAME: PlayerSM::setupStateMachineLinks
void __thiscall PlayerSM::setupStateMachineLinks(void* thisPtr)
{
    int* pLocal;
    int* pNode;
    int* pTarget;
    int* pTemp;
    int* pLink1;
    int* pLink2;
    int* pOwnerList;
    int result;
    char bResult;
    int* pSingleton;
    int local_4;

    // Set state to 0x101 (likely a specific state ID)
    *(short*)((char*)thisPtr + 0x7d) = 0x101;
    local_4 = (int)thisPtr;

    pSingleton = (int*)FUN_007ab690(); // Singleton manager
    if (pSingleton == nullptr)
    {
        bResult = FUN_00481620(); // Check some initialization flag
        if (bResult == '\0')
        {
            return;
        }
        // Initialize fields
        *(int*)((char*)thisPtr + 0x94) = 0;
        *(int*)((char*)thisPtr + 0x104) = 0;
        *(int*)((char*)thisPtr + 0x184) = *(int*)(*(int*)((char*)thisPtr + 0x58) + 0x3180);
        FUN_0081b030(*(int*)((char*)thisPtr + 0x58), (undefined4*)((char*)thisPtr + 0x94), 1);
        FUN_0081db00((undefined4*)((char*)thisPtr + 0x94));
        if (*(int*)((char*)thisPtr + 0x110) == 0)
        {
            return;
        }
        pNode = (int*)(*(int*)((char*)thisPtr + 0x110) - 0x48); // Cast to parent object
        if (pNode == nullptr)
        {
            return;
        }
    }
    // Virtual call on pNode: vtable+0x10 takes hash(0x55859efa) and outputs pointer to local_4
    local_4 = 0;
    bResult = ((int (__thiscall*)(int, int, int*))(*(int*)(*pNode + 0x10)))((int)pNode, 0x55859efa, &local_4);
    if ((bResult == '\0') || (local_4 == 0))
    {
        // Clear secondary state flag
        *(char*)((char*)thisPtr + 0x198) = 0;
    }
    else
    {
        *(short*)((char*)thisPtr + 0x90) |= 1; // Set bit 0 in flags
        *(char*)((char*)thisPtr + 0x198) = *(char*)(local_4 + 0x1b8c); // Copy byte from target
        FUN_0043b870(DAT_01131018); // Play some global sound
        bResult = FUN_009af6f0(*(int*)((char*)thisPtr + 0x58)); // Check ownership
        if (bResult == '\0')
        {
            *(short*)((char*)thisPtr + 0x90) |= 0x10; // Set bit 4 in flags
        }
    }

    // Insert self into two linked lists (transitions?) 
    pTarget = pNode + 0x12; // pNode + 0x48 bytes
    pLink1 = (int*)((char*)thisPtr + 0x188);
    if (*pLink1 != pTarget)
    {
        if (*pLink1 != nullptr)
        {
            FUN_004daf90(pLink1); // Remove from old list
        }
        *pLink1 = (int)pTarget; // Set next to target
        if (pTarget != nullptr)
        {
            *(int*)((char*)thisPtr + 0x18c) = pNode[0x13]; // Set prev to old head
            pNode[0x13] = (int)pLink1; // Update head to point to this
        }
    }

    pLink2 = (int*)((char*)thisPtr + 0x190);
    if (*pLink2 != pTarget)
    {
        if (*pLink2 != nullptr)
        {
            FUN_004daf90(pLink2); // Remove from old list
        }
        *pLink2 = (int)pTarget;
        if (pTarget != nullptr)
        {
            *(int*)((char*)thisPtr + 0x194) = pNode[0x13];
            pNode[0x13] = (int)pLink2;
        }
    }

    // Also update the owner's list at +0x1c78
    pOwnerList = (int*)(*(int*)((char*)thisPtr + 0x58) + 0x1c78);
    pTemp = (*pLink1 != 0) ? (int*)(*pLink1 - 0x48) : nullptr;
    int owner = *(int*)((char*)thisPtr + 0x58);
    pNode = (int*)(owner + 0x1c78);
    if (pTemp == nullptr)
    {
        pTemp = nullptr;
    }
    else
    {
        pTemp = (int*)((char*)pTemp + 0x48);
    }
    if (*pNode != (int)pTemp)
    {
        if (*pNode != 0)
        {
            FUN_004daf90(pNode);
        }
        *pNode = (int)pTemp;
        if (pTemp != nullptr)
        {
            *(int*)(owner + 0x1c7c) = *(int*)((char*)pTemp + 4);
            *(int**)((char*)pTemp + 4) = pNode;
        }
    }
    return;
}