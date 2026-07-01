// Xbox PDB: EARS_Modules_PlayerRecoverStateMachine_BuildRecoverStateTable
// FUNC_NAME: PlayerRecoverStateMachine::initialize

void PlayerRecoverStateMachine::initialize(void)
{
    uint32_t tableId;
    int32_t tableExists;

    tableId = GameState::getStateTable("PlayerRecoverStateTable");
    tableExists = GameState::isStateTablePresent(tableId);
    if (tableExists == 0) {
        void* stateMachine = GameState::createNewStateMachine();
        GameState::initStateTable("PlayerRecoverStateTable", stateMachine);

        // --- "recoverInit" state ---
        GameState::addState("recoverInit", 0xffffffff);          // no parent
        GameState::setStateDesc(0x31, 0xc, 1);                   // state ID 0x31, flags 0xc, value 1
        GameState::addTransition("crawlToStandBlocking", 0x10, 3, 1);
        GameState::addTransition("crawlToStandBlocking", 0x10, 2, 1);
        GameState::addTransition("kneelToStandBlocking", 0x10, 1, 1);
        GameState::addFinalState("terminate", 4);

        // --- "beginStun" state ---
        GameState::addState("beginStun", 0xffffffff);
        GameState::setStateDesc(0x32, 2, 1);                    // state ID 0x32
        GameState::addTransitionHash(0xfe89478a, 1, 1, 0, 1.0f); // hash, from, to, condition, blend
        GameState::setStateTimer(8);                             // 8 frames/seconds?
        GameState::addFinalState("stunned", 7);

        // --- "stunned" state ---
        GameState::addState("stunned", 0xffffffff);
        GameState::setStateTimerSet(0x33);                      // timer set ID 0x33
        GameState::addTransitionHash(0xde2d941c, 1, 1, 0, 1.0f);
        GameState::setStateTimer(8);
        GameState::addFinalState("endStun", 0x13);

        // --- "endStun" state ---
        GameState::addState("endStun", 0xffffffff);
        GameState::setStateDesc(0x32, 2, 1);
        GameState::addTransitionHash(0x15635483, 1, 1, 0, 1.0f);
        GameState::setStateTimer(8);
        GameState::setStateTransitionParam(0x31, 2, 1);         // state 0x31, param 2, value 1
        GameState::addFinalState("terminate", 7);

        // --- "crawlToStandBlocking" state ---
        GameState::addState("crawlToStandBlocking", 0xffffffff);
        GameState::setStateTimerSet(0x35);
        GameState::setStateTimerSet(0x34);
        GameState::setStateTimer(8);
        GameState::setStateTimerFromTo(0x36);                   // timer range?
        GameState::addFinalState("terminate", 7);

        // --- "kneelToStandBlocking" state ---
        GameState::addState("kneelToStandBlocking", 0xffffffff);
        GameState::setStateTimerSet(0x35);
        GameState::setStateTimerSet(0x34);
        GameState::setStateTimer(8);
        GameState::setStateTimerFromTo(0x36);
        GameState::addFinalState("terminate", 7);

        // --- "terminate" state ---
        GameState::addState("terminate", 0xffffffff);
        GameState::setStateTimerSet(2);

        // Finalize state machine
        GameState::finalizeStateMachine(0xbabf279, &LAB_007eaf60, "PlayerRecoverStateMachine");
        GameState::compileStateMachine();
    }
}