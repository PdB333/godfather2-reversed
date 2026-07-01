// FUNC_NAME: PlayerSM::checkStateAndTrigger
void __fastcall PlayerSM::checkStateAndTrigger(int this) {
    // Check if current state is not 1 (e.g., kStateIdle) and is 3 (e.g., kStateActive)
    int currentState = *(int*)(this + 4); // +0x04: m_currentState
    if (currentState != 1 && currentState == 3) {
        triggerEvent(1); // Notify state change with parameter 1
    }
}