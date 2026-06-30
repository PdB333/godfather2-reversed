// FUNC_NAME: Entity::updateBusyFlag
void __thiscall Entity::updateBusyFlag(bool enable, Entity* exceptEntity, bool ignoreCondition)
{
    ComponentManager* compMgr = *(ComponentManager**)(this + 0x18); // +0x18
    if (enable)
    {
        int count = *(int*)(compMgr + 0x154); // m_componentCount
        ComponentBase** compList = *(ComponentBase***)(compMgr + 0x150); // m_componentList
        for (int i = 0; i < count; i++)
        {
            ComponentBase* comp = compList[i];
            if (*(char*)(comp + 0x18) == 1) // m_type == 1 (relative data)
            {
                int offset = *(signed char*)(comp + 0x10); // m_dataOffset (signed)
                Entity* dataEntity = (Entity*)((char*)comp + offset);
                // Check if dataEntity is valid and not in a specific state (0x07)
                if (dataEntity != nullptr && *(char*)(dataEntity + 0xd8) != 0x07 && dataEntity != exceptEntity)
                {
                    return; // Early exit: condition prevents setting busy flag
                }
            }
            bool conditionResult = checkSomeCondition(); // FUN_0054ea60
            if (conditionResult && !ignoreCondition)
            {
                return; // External condition also prevents
            }
        }
        // All conditions passed, set flags
        *(uint*)(this + 0xe4) |= 0x40; // m_flags |= kBusyFlag (0x40)
        *(uint*)(this + 0xe4) |= 0x100; // m_flags |= kAnotherFlag (0x100)
    }
    else
    {
        // Clear busy flag, keep another flag set
        *(uint*)(this + 0xe4) &= ~0x40; // Clear kBusyFlag
        *(uint*)(this + 0xe4) |= 0x100; // Set kAnotherFlag
    }
}