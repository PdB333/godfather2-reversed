// Xbox PDB: EARS_Modules_LadderClimbSM_BuildStateMachine
// FUNC_NAME: LadderClimbStateMachine::initialize
void LadderClimbStateMachine::initialize(void)
{
    // Get the state machine manager instance
    StateMachineManager* manager = StateMachineManager::getInstance();
    
    // Register the ladder climb state table
    manager->registerStateTable("LadderClimbStateTable", manager);
    
    // Set default transition for all states to -1 (no transition)
    manager->setDefaultTransition(-1);
    
    // Add states with their IDs
    manager->addState(0x0D);  // State: idle
    manager->addState(0x12);  // State: climbing
    manager->addState(0x13);  // State: stepOffTop
    
    // Add state transitions with names and target state IDs
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("inactiveLadderExit", 0x14);
    manager->addTransition("ladderEnterDirection", 3);
    
    // Override default transition for ladderEnterDirection
    manager->setDefaultTransition("ladderEnterDirection", -1);
    
    // Re-add some transitions (likely for state machine setup)
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("inactiveLadderExit", 0x14);
    manager->addTransition("stepOnLadderBottom", 10);
    manager->addTransition("stepOnLadderTop", 0x0B);
    
    // Override default transition for stepOnLadderBottom
    manager->setDefaultTransition("stepOnLadderBottom", -1);
    
    // Set state flags (unknown parameters: hash, bool1, bool2, bool3, float)
    manager->setStateFlags(0x16EE5808, 1, 1, 1, 1.0f);
    manager->addState(0x16);
    manager->addState(8);
    manager->removeState(8);
    
    // Add transitions for state 0x16
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("inactiveLadderExit", 0x14);
    manager->addTransition("ladderIdle", 7);
    
    // Override default transition for stepOnLadderTop
    manager->setDefaultTransition("stepOnLadderTop", -1);
    
    // Set state flags for another state
    manager->setStateFlags(0xA3477C8F, 1, 1, 1, 1.0f);
    manager->addState(0x17);
    manager->addState(0x1F);
    manager->addState(8);
    manager->removeState(8);
    
    // Add transitions for state 0x17
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("inactiveLadderExit", 0x14);
    manager->addTransition("ladderIdle", 7);
    
    // Set state entry action
    manager->setStateEntryAction(0x20);
    
    // Override default transition for climbToIdle
    manager->setDefaultTransition("climbToIdle", -1);
    
    // Add states for climbing
    manager->addState(0x1A);
    manager->addState(8);
    manager->removeState(8);
    
    // Add transitions for climbing state
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("inactiveLadderExit", 0x14);
    manager->addTransition("stepOffLadderBottom", 0x10);
    manager->addTransition("clearVelocityAndExit", 0x0F);
    manager->addTransition("stepOffLadderTop", 0x11);
    manager->addTransition("ladderIdle", 7);
    
    // Set state entry action
    manager->setStateEntryAction(0x1C);
    
    // Override default transition for ladderIdle
    manager->setDefaultTransition("ladderIdle", -1);
    
    // Add states for ladder idle
    manager->addState(0x1D);
    manager->addState(0x1B);
    manager->addState(8);
    
    // Set state animation (unknown parameters: stateID, animID, unknown)
    manager->setStateAnimation(10, 0x49, 1);
    
    // Remove states
    manager->removeState(0x1D);
    manager->removeState(8);
    manager->removeState(0x21);
    
    // Add transitions for ladder idle
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("inactiveLadderExit", 0x14);
    manager->addTransition("clearVelocityAndExit", 0x0F);
    manager->addTransition("climbing", 0x0E);
    manager->addTransition("stepOffLadderBottom", 0x10);
    manager->addTransition("stepOffLadderTop", 0x11);
    
    // Set state animation for climbing
    manager->setStateAnimation(0x0B, 0x49, 1);
    
    // Override default transition for climbing
    manager->setDefaultTransition("climbing", -1);
    
    // Add states for climbing
    manager->addState(0x19);
    manager->addState(0x1A);
    manager->addState(0x1D);
    manager->addState(8);
    manager->removeState(8);
    
    // Add transitions for climbing
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("inactiveLadderExit", 0x14);
    manager->addTransition("clearVelocityAndExit", 0x0F);
    manager->addTransition("ladderIdle", 0x0D);
    manager->addTransition("climbToIdle", 0x0C);
    manager->addTransition("stepOffLadderBottom", 0x10);
    manager->addTransition("stepOffLadderTopWait", 0x11);
    manager->addTransition("climbing", 7);
    
    // Override default transition for stepOffLadderBottom
    manager->setDefaultTransition("stepOffLadderBottom", -1);
    
    // Set state flags
    manager->setStateFlags(0x5E06FC08, 1, 1, 1, 1.0f);
    manager->addState(8);
    manager->removeState(8);
    
    // Add transitions for stepOffLadderBottom
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("clearVelocityAndExit", 7);
    
    // Override default transition for stepOffLadderTop
    manager->setDefaultTransition("stepOffLadderTop", -1);
    
    // Set state flags
    manager->setStateFlags(0x2F444401, 1, 1, 1, 1.0f);
    manager->addState(0x1F);
    manager->addState(8);
    manager->removeState(8);
    
    // Add transitions for stepOffLadderTop
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("clearVelocityAndExit", 7);
    
    // Set state entry action
    manager->setStateEntryAction(0x20);
    
    // Override default transition for stepOffLadderTopWait
    manager->setDefaultTransition("stepOffLadderTopWait", -1);
    
    // Add states for stepOffLadderTopWait
    manager->addState(0x1D);
    manager->addState(0x1B);
    manager->addState(8);
    manager->removeState(8);
    manager->removeState(0x21);
    
    // Add transitions for stepOffLadderTopWait
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("stepOffLadderTop", 0x13);
    
    // Override default transition for inactiveLadderExit
    manager->setDefaultTransition("inactiveLadderExit", -1);
    
    // Add states for inactiveLadderExit
    manager->addState(0x1E);
    
    // Add transitions for inactiveLadderExit
    manager->addTransition("ragdollDeath", 0x16);
    manager->addTransition("clearVelocityAndExit", 4);
    
    // Override default transition for ragdollDeath
    manager->setDefaultTransition("ragdollDeath", -1);
    
    // Add states for ragdollDeath
    manager->addState(0x22);
    
    // Add transitions for ragdollDeath
    manager->addTransition("terminate", 0x17);
    
    // Override default transition for clearVelocityAndExit
    manager->setDefaultTransition("clearVelocityAndExit", -1);
    
    // Add states for clearVelocityAndExit
    manager->addState(0x0D);
    
    // Add transitions for clearVelocityAndExit
    manager->addTransition("terminate", 4);
    
    // Override default transition for terminate
    manager->setDefaultTransition("terminate", -1);
    
    // Add final state
    manager->addState(2);
    
    // Register the state machine with a hash and function pointer
    manager->registerStateMachine(0x8ADE428D, &LadderClimbStateMachine::update, "LadderClimbSM");
    
    // Finalize initialization
    manager->finalize();
}