// FUNC_NAME: PlayerSM::commitTransition
void __thiscall PlayerSM::commitTransition()
{
    // Disable input or lock player controls during transition
    FUN_007ac770(1);  // Likely g_inputManager->lockInput(true) or similar

    // Notify state manager about the previous state's exit
    FUN_007ac6f0(*(int*)((char*)this + 0x7c));  // +0x7c: m_pStateManager or m_pPreviousStateData

    // Copy the previous state value (or flags) into the current state
    *(int*)((char*)this + 0x84) = *(int*)((char*)this + 0x80);  // +0x80: m_previousState, +0x84: m_currentState
}