// FUNC_NAME: PlayerSM::updateState
void PlayerSM::updateState()
{
    // offset +0x14: pointer to state context structure
    StateContext* stateContext = *(StateContext**)((char*)this + 0x14);

    if (stateContext->state == 1)
    {
        // handle state 1 (e.g., Idle)
        handleState1();
        return;
    }

    if (stateContext->state == 3)
    {
        // handle state 3 (e.g., Moving)
        handleState3();
        return;
    }

    // default case: transition to state 6, reset timer
    stateContext->state = 6;        // +0xb0: state id
    stateContext->timer = 0;        // +0xb8: state timer

    // global singleton at DAT_012234a8; increment counter at +0x90
    ((GameManager*)0x012234a8)->stateTransitionCount++;
}