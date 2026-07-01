// FUNC_NAME: StateMachineBuilder::buildCoverBlindFire
void StateMachineBuilder::buildCoverBlindFire(void)
{
    // Get a unique ID for the state machine (e.g., from a global counter or hash)
    uint stateMachineID = StateMachineManager::allocateID();          // FUN_009c8f80

    // Register the state machine with a name and ID
    StateMachineManager::registerMachine("CoverBlindFireST", stateMachineID); // FUN_004ad9d0

    // Set a default parameter or transition for the whole machine (0xffffffff = invalid/max)
    StateMachineManager::setParameter("CoverBlindFireST", 0xffffffff);        // FUN_004adae0

    // Push a state (0xC = 12)
    StateMachineManager::pushState(0xC);                                      // FUN_004acf70

    // Set the state table for "trackToPositionAndDirectionStateTable" to state 1
    StateMachineManager::setStateTable("trackToPositionAndDirectionStateTable", 1); // FUN_004acf10

    // Add a transition label "checkExpose" to state 1
    StateMachineManager::addTransition("checkExpose", 1);                     // FUN_004acc70

    // Set default parameter for "checkExpose" (0xffffffff = none)
    StateMachineManager::setParameter("checkExpose", 0xffffffff);             // FUN_004adae0

    // Push state 0x23 (35)
    StateMachineManager::pushState(0x23);                                     // FUN_004acf70

    // Add transition from state 0x12 (18) with some internal label (likely a data reference)
    StateMachineManager::addTransition(&DAT_00d63afc, 0x12);                  // FUN_004acc70

    // Add transition "blindFire" to state 0x13 (19)
    StateMachineManager::addTransition("blindFire", 0x13);                    // FUN_004acc70

    // Set default parameter for "blindFire" (0xffffffff)
    StateMachineManager::setParameter("blindFire", 0xffffffff);               // FUN_004adae0

    // Push states 0x23, 0x24, 0x25 (35,36,37) – likely sub-states
    StateMachineManager::pushState(0x23);                                     // FUN_004acf70
    StateMachineManager::pushState(0x24);                                     // FUN_004acf70
    StateMachineManager::pushState(0x25);                                     // FUN_004acf70

    // Set number of states to 0x1F (31) – maybe cap or config
    StateMachineManager::setStateCount(0x1F);                                 // FUN_004acff0

    // Add transition from the internal label to state 7
    StateMachineManager::addTransition(&DAT_00d63afc, 7);                     // FUN_004acc70

    // Set default parameter for that internal label
    StateMachineManager::setParameter(&DAT_00d63afc, 0xffffffff);             // FUN_004adae0

    // Push state 2
    StateMachineManager::pushState(2);                                        // FUN_004acf70

    // Register the state machine with a CRC (0x1f18954e), label (function pointer), and name
    StateMachineManager::registerMachineWithCRC(0x1f18954e, &LAB_00765590, "CoverBlindFireSM"); // FUN_004adc90

    // Finalize/commit the state machine
    StateMachineManager::finalize();                                          // FUN_004ada40
    return;
}