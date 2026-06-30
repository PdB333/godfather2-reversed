// FUNC_NAME: MissionManager::SetObjectiveParameter
void __thiscall MissionManager::SetObjectiveParameter(int this, int objectiveIndex, unsigned int parameterValue)
{
    // +0x218: pointer to objective list manager
    int* pObjectiveListMgr = *(int**)(this + 0x218);
    if (pObjectiveListMgr == 0 || objectiveIndex < 0)
        return;

    // +0x124: first objective node pointer (list head)
    int* currentNode = *(int**)(pObjectiveListMgr + 0x124);
    // Traverse the linked list to the desired index
    for (int i = 0; i < objectiveIndex; i++)
    {
        if (currentNode == 0)
            return;
        // +0x124: next node in the list
        currentNode = *(int**)(currentNode + 0x124);
    }
    if (currentNode != 0)
    {
        // +0x130: parameter data field on each objective node
        *(unsigned int*)(currentNode + 0x130) = parameterValue;
    }
}