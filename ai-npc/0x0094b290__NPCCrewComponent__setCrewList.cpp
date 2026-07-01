// FUNC_NAME: NPCCrewComponent::setCrewList
void __thiscall NPCCrewComponent::setCrewList(NPCCrewComponent* this, CrewList* sourceList)
{
    uint index = 0;
    this->m_crewCount = 0; // +0x198
    releaseCrewArray(this->m_crewArray); // FUN_009c8f10, +0x194
    this->m_crewArray = nullptr; // +0x194
    this->m_crewCapacity = 0; // +0x19c
    if (sourceList != nullptr && sourceList->count != 0) {
        do {
            int* elementPtr = *(int**)(sourceList->arrayBase + 4 + index * 8);
            int** storage = (int**)addCrewMember(&elementPtr); // FUN_006b4d50
            *storage = elementPtr;
            index++;
        } while (index < sourceList->count);
    }
    notifyCrewChanged(*(int*)(DAT_0112a66c + 8), 1); // FUN_0094a610
}