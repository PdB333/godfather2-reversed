// FUNC_NAME: ObjectiveManager::processObjectives
// Function address: 0x00976d00
// Role: Iterates through a list of objectives (or entities) and triggers an action based on type and state.
// Calls: getObjectiveList (0x849cf0), checkObjectiveState (0x8ff310), applyObjectiveEffect (0x6b5360)

void __thiscall ObjectiveManager::processObjectives(float dt)
{
    ObjectiveList* pList = getObjectiveList(this->m_pObjectiveListManager); // +0x13c
    if (pList != nullptr && pList->m_nCount != 0) { // +0x98
        uint i = 0;
        do {
            Objective* pObj = pList->m_ppObjectives[i]; // +0x94 (array of pointers)
            // Check if objective type is not 9 (e.g., "completed") 
            // OR if type is 9 but the objective is still active (checkObjectiveState returns non-zero)
            if (pObj->m_type != 9 || checkObjectiveState(pObj->m_someHandle)) { // +0xc4, +0x38
                applyObjectiveEffect(1, dt); // +0x6b5360 (e.g., trigger event or update timer with param=1)
            }
            i++;
        } while (i < pList->m_nCount);
    }
}