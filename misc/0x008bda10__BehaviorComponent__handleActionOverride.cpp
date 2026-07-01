// FUNC_NAME: BehaviorComponent::handleActionOverride
void __thiscall BehaviorComponent::handleActionOverride(ActionContext* context, StateData* stateData)
{
    int actionId;
    int extraData;
    bool bPaused;

    bPaused = isPaused(); // FUN_00791230
    Entity* entity = stateData->m_entity; // +0x08
    bool ignorePauseFlag = (*(uint*)(entity + 0x5C) >> 0x14) & 1; // bit 20

    if (!bPaused || ignorePauseFlag)
    {
        // Not paused or entity allows updates during pause
        if (stateData->m_state != 7) // +0x04 (state enum, 7 = some blocked state)
        {
            setAction(*(int*)(context + 0x38)); // action id from context
            beginAction(3, 0);
        }
    }
    else
    {
        // Paused and entity does not ignore pause
        actionId = getCurrentActionId(); // FUN_008c8180
        if (actionId == 0)
        {
            if (stateData->m_state != 7)
            {
                setAction(0);
                beginAction(1, 0);
            }
        }
        else
        {
            extraData = *(int*)(this + 0x1E0); // some field, e.g., action param
            if (stateData->m_state != 7)
            {
                setAction(actionId);
                beginAction(3, extraData);
            }
        }
    }
}