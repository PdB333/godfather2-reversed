// FUN_004aba80: AIAction::deactivateOnCondition
void AIAction::deactivateOnCondition(int conditionType, int targetId, int value1, int value2, int value3)
{
    int conditionResult = isConditionMet(conditionType, targetId, value1, value2, value3);
    if (conditionResult != 0) {
        this->m_field38 = 0; // +0x38, likely m_bIsActive or m_nTimer
    }
}