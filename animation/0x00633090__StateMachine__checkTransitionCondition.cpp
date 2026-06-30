// FUNC_NAME: StateMachine::checkTransitionCondition
bool __thiscall StateMachine::checkTransitionCondition(int stateIndex) {
    // this +0x0C: pointer to transition data table (with 4-byte header)
    uint* table = *(uint**)(this + 0x0C);
    uint entry = *(uint*)((char*)table + 4 + stateIndex * 4);
    uint conditionType = entry & 0x3F;

    if (conditionType > 0x18) {
        if (conditionType < 0x1C) {
            // condition types 0x19-0x1B: upper bits (16-22) must be clear
            return (entry & 0xFF8000) == 0;
        }
        if (conditionType == 0x20) {
            // condition type 0x20: always allowed
            return true;
        }
    }
    return false;
}