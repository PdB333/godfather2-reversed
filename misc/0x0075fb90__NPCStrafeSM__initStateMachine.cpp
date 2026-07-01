// FUNC_NAME: NPCStrafeSM::initStateMachine
void NPCStrafeSM::initStateMachine(void)
{
    // Get the FSM manager instance
    FSMManager* pFSMManager = FSMManager::getInstance(); // FUN_009c8f80

    // Create the main strafe state
    pFSMManager->createState("NPCStrafeST"); // FUN_004ad9d0

    // Set default transition (any state -> -1 signifies no destination? or global transition?)
    pFSMManager->setTransition(g_strUnknownState, 0xFFFFFFFF); // FUN_004adae0(&DAT_00d63420, -1)

    // Add conditions for the strafe state
    pFSMManager->addCondition("blocked", 10);   // FUN_004acc70
    pFSMManager->addCondition("strafe", 4);     // FUN_004acc70

    // Set transition from strafe state (to what? -1 means end?)
    pFSMManager->setTransition("strafe", 0xFFFFFFFF); // FUN_004adae0

    // Set state timeout for state index 5 (?) with event 0x4020 and param 1
    pFSMManager->setStateTimeout(5, 0x4020, 1); // FUN_004ad0f0

    // Set initial state to FollowPathST
    pFSMManager->setInitialState("FollowPathST", 1); // FUN_004acf10

    // Add condition "blocked" again in FollowPathST context
    pFSMManager->addCondition("blocked", 10);   // FUN_004acc70

    // Add path error transitions
    pFSMManager->addTransition("pathErrorNoPath", 6, 0x4000, 1); // FUN_004acd20
    pFSMManager->addTransition("pathError", 6, 0x20, 1);         // FUN_004acd20

    // Add success condition
    pFSMManager->addCondition("success", 1);    // FUN_004acc70

    // Set transition from pathError to -1 (clear)
    pFSMManager->setTransition("pathError", 0xFFFFFFFF); // FUN_004adae0

    // Set state timeouts for states 4 and 6
    pFSMManager->setStateTimeout(4, 0x20, 1);   // FUN_004ad0f0
    pFSMManager->setStateTimeout(6, 0x20, 1);   // FUN_004ad0f0

    // Set conditions for blocked state (value 4)
    pFSMManager->addCondition("blocked", 4);    // FUN_004acc70

    // Set transition for pathErrorNoPath to -1
    pFSMManager->setTransition("pathErrorNoPath", 0xFFFFFFFF); // FUN_004adae0

    // Set state timeouts for states 4 and 6 with different events
    pFSMManager->setStateTimeout(4, 0x4000, 1); // FUN_004ad0f0
    pFSMManager->setStateTimeout(6, 0x4020, 1); // FUN_004ad0f0

    // Add condition for pathError with value 4
    pFSMManager->addCondition("pathError", 4);  // FUN_004acc70

    // Set transition from blocked to -1
    pFSMManager->setTransition("blocked", 0xFFFFFFFF); // FUN_004adae0

    // Add state with index 10 (?) and a condition from global string
    pFSMManager->addStateIndex(10);             // FUN_004acf70
    pFSMManager->addCondition(g_strAnotherUnknown, 4); // FUN_004acc70(&DAT_00d63afc, 4)

    // Set transition from success to -1
    pFSMManager->setTransition("success", 0xFFFFFFFF); // FUN_004adae0

    // Add state with index 11
    pFSMManager->addStateIndex(11);             // FUN_004acf70
    pFSMManager->addCondition(g_strAnotherUnknown, 4); // FUN_004acc70(&DAT_00d63afc, 4)

    // Set transition from the global string state to -1
    pFSMManager->setTransition(g_strAnotherUnknown, 0xFFFFFFFF); // FUN_004adae0

    // Add state with index 2
    pFSMManager->addStateIndex(2);              // FUN_004acf70

    // Register the state machine class with its constructor and name
    // Hash 0xf33262ca is probably a CRC of "NPCStrafeSM"
    pFSMManager->registerStateMachine(0xf33262ca, &NPCStrafeSM::constructor, "NPCStrafeSM"); // FUN_004adc90

    // Finalize the state machine creation
    pFSMManager->finalizeSetup(); // FUN_004ada40

    return;
}