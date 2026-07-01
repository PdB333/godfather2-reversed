// FUNC_NAME: SimManager::processList
void __fastcall SimManager::processList(SimManager* this)
{
    bool bCondition; // cVar1
    int* pList; // iVar2 - pointer to list container
    uint i; // uVar3

    // +0x13c: likely pointer to a container (e.g., array of some objects)
    pList = getListFromOffset(*(uint*)(this + 0x13c));
    if ((pList != nullptr) && (*(int*)(pList + 0x98) != 0)) // +0x98: count of items in the container
    {
        for (i = 0; i < *(uint*)(pList + 0x98); i++)
        {
            // Global check – possibly a random trigger or per-frame condition
            bCondition = checkRandomCondition();
            if (bCondition)
            {
                // Action with parameter 0 – likely reset/initialize something
                callAction(0);
            }
        }
    }
}