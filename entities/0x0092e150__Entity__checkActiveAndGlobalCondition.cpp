// FUNC_NAME: Entity::checkActiveAndGlobalCondition
bool __fastcall Entity::checkActiveAndGlobalCondition(Entity *this)
{
    // +0x124: m_isActive (byte flag)
    if (this->m_isActive)
    {
        // Calls a global condition function (originally FUN_0089c630)
        if (isGlobalConditionMet())
        {
            return true;
        }
    }
    return false;
}