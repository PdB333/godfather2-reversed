// FUNC_NAME: NPC::tickAI
// Address: 0x00643560
// Role: Updates the NPC's AI state machine, processing optional events or performing normal tick.

void NPC::tickAI(int eventId)
{
    // stateMachine points to the NPC's state machine structure (loaded in EDI)
    int* stateMachine;   // unaff_EDI
    int result;          // iVar1

    if (eventId != 0) {
        // Handle an incoming event and exit
        handleEvent(eventId);
        return;
    }

    // Normal update – no event
    preUpdate();

    // If current state is 4 and a condition derived from the state index holds…
    // (Check: state = 4 and table[owner +8][stateMachine[1]*8] == 3)
    if ((*stateMachine == 4) && (*(int*)(*(int*)(this + 8) + stateMachine[1] * 8) == 3)) {
        result = calculateValue();
        stateMachine[1] = result;
        return;
    }

    // Fallback update path
    alternativeUpdate();

    // If state is 11 (0xb) and the state timer is within [owner->threshold, 0xfa)
    if ((*stateMachine == 11) && (this[0xd] <= stateMachine[1] && stateMachine[1] < 0xfa)) {
        // Decrement the NPC's counter (offset +0x24)
        this[9] = this[9] - 1;
    }

    // Build a 16-bit message from the state timer and send it
    result = sendMessage(stateMachine[1] << 0xf | 0x11, *(void**)(this[3] + 8));
    stateMachine[1] = result;
    *stateMachine = 10;  // Transition to state 10
    return;
}