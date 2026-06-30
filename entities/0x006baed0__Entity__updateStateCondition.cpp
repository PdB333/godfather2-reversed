// FUNC_NAME: Entity::updateStateCondition
uint __fastcall Entity::updateStateCondition(Entity* this)
{
    char localBuffer[12]; // unused buffer, possibly for time or position query
    char conditionResult;

    // Check if condition object exists and if the evaluation hasn't been done yet (bit 30 cleared?)
    if ((this->m_conditionObject != 0) && ((this->m_stateFlags & 0x40000000) == 0))
    {
        // Evaluate condition: call a function on the condition object's internal state at +0x28
        conditionResult = CheckCondition(this->m_conditionObject + 0x28, localBuffer);
        if (conditionResult == 0)
        {
            // Clear bit 31 (condition false)
            this->m_stateFlags &= 0x7FFFFFFF;
        }
        else
        {
            // Set bit 31 (condition true)
            this->m_stateFlags |= 0x80000000;
        }
        // Set bit 30 to indicate this condition has been evaluated
        this->m_stateFlags |= 0x40000000;
    }
    // Return the current condition result (bit 31)
    return (this->m_stateFlags >> 0x1F) & 1;
}