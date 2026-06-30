// FUNC_NAME: Player::canStartAction
bool Player::canStartAction() {
    // +0x328: dead flag (m_bIsDead)
    // +0x2d0: state machine pointer (m_pStateMachine)
    // +0x334: current action ID (m_uCurrentAction)
    int deadFlag = *(int*)(this + 0x328);
    int stateMachine = *(int*)(this + 0x2d0);
    if (deadFlag == 0 && stateMachine != 0) {
        int actionId = *(int*)(this + 0x334);
        int validationResult = FUN_00700090(actionId); // isActionValid
        if (validationResult + deadFlag != 0) {
            return true;
        }
    }
    return false;
}