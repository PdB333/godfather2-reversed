// FUNC_NAME: Player::determineDodgeAction
void __thiscall Player::determineDodgeAction(Player* this, int param2, int param3)
{
    int index;
    char byteVal;
    int randVal;
    bool invertFlag;
    char local_buffer[48];
    int local_18;
    int local_4;
    unsigned int decision;

    index = getCombatStateIndex();
    if (index == 0) {
        index = 0;
    } else {
        index = index - 0x58;
        if (index != 0) {
            byteVal = getRandomByte(); // random seed byte
            decision = (decision & 0xffffff00) | (byteVal & 0xff);
            goto LAB_CONTINUE;
        }
    }
    // fallback: shift high bytes low? (unusual, possibly a bug in decompilation)
    decision = (decision >> 8) & 0xffffff;

LAB_CONTINUE:
    if (checkActionPossible(decision) != '\0' && index != 0) {
        if (checkSecondaryCondition() != '\0' &&
            (*(char *)(this + 0x2454) != '\0' && *(char *)(this + 0x2470) != '\0')) {
            decision = (decision & 0xffffff00) | 1; // default "dodge forward"?
            if (isRandomAllowed(0x17) != '\0') {
                randVal = _rand();
                randVal = randVal & 0x80000001;
                invertFlag = (randVal == 0);
                if ((int)randVal < 0) {
                    invertFlag = ((randVal - 1) | 0xfffffffe) == 0xffffffff;
                }
                decision = (decision & 0xffffff00) | (invertFlag ? 0 : 1); // random invert
            }
            debugLogFunction();
            incrementCounter(index);
            incrementCounter(index);
            local_18 = 2;
            local_4 = 4;
            // Use this+0x3c as string source (likely debug name)
            int namePtr = (this != 0) ? (int)(this + 0x3c) : 0;
            formatString(&DAT_0112dd94, namePtr, local_buffer, 0);
            executeDodgeAction(param2, param3, decision);
            setDodgeAnimationState(index, this, decision);
            finalizeDodgeAction();
        }
    }
}