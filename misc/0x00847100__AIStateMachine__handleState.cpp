// FUNC_NAME: AIStateMachine::handleState
int __fastcall AIStateMachine::handleState(int this)
{
    int stateId;
    // Get pointer to state data at this+0xFC (likely m_pStateData)
    int* stateData = *(int**)(this + 0xFC);
    // Look up state info using the key at stateData[2] (offset +8)
    stateId = FUN_004025a0(stateData[2]);
    if (stateId == 0) {
        stateId = -1;
    } else {
        stateId = *(int*)(stateId + 0x24);  // state field at offset 0x24
    }
    // 3 – terminal state (do nothing, return 0)
    if (stateId == 3) return 0;
    // 0 and 1 – special states that skip processing
    if ((stateId != 0) && (stateId != 1)) {
        // Process state transition: this, subject (stateData[1]), and target key pointer (&stateData[2])
        FUN_00846b90(this, stateData[1], &stateData[2]);
    }
    return 1;
}