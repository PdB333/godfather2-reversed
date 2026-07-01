// FUNC_NAME: PlayerSM::handleMessage
int __thiscall PlayerSM::handleMessage(int newState) {
    int currentState = GetCurrentState(); // FUN_00466840

    if (newState == currentState) {
        if (*(char *)(this + 0x170) != '\0') { // +0x170: m_bReentrantFlag
            enterStateCurrent(); // FUN_0092df50
            return 0;
        }
    } else {
        switch (newState) {
        case 2:
            enterState2(); // FUN_00930460
            return 0;
        case 4:
            enterState4(); // FUN_009304f0
            break;
        case 8:
            enterState8(); // FUN_0092d600
            return 0;
        case 9:
            enterState9(); // FUN_0092dfd0
            return 0;
        }
    }
    return 0;
}