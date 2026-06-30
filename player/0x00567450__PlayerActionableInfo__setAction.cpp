// FUNC_NAME: PlayerActionableInfo::setAction
void __thiscall PlayerActionableInfo::setAction(int this, int actionData)
{
    // Set action data (e.g., target or parameter for the action)
    *(int*)(this + 0x18) = actionData;   // +0x18: m_actionData
    // Set subtype to a default value (2 likely corresponds to a specific state/phase)
    *(byte*)(this + 0x14) = 2;           // +0x14: m_actionSubType
    // Set main action type to 9 (e.g., "attack" or "cover" or other predefined action)
    *(int*)(this + 0x10) = 9;            // +0x10: m_actionType
}