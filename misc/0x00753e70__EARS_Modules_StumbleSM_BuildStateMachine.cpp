// Xbox PDB: EARS::Modules::StumbleSM::BuildStateMachine
// FUNC_NAME: initializeStumbleStateMachine
void initializeStumbleStateMachine(void)
{
    // Look up the already registered stumble state table
    stateMachineHandle handle = stateMachineManager::lookupStateMachine("stumbleStateTable");
    
    // If it doesn't exist yet, create and configure it
    if (handle == NULL) {
        // Allocate a new state machine handle
        handle = stateMachineManager::createStateMachine();
        
        // Register it with the name "stumbleStateTable"
        stateMachineManager::registerStateMachine("stumbleStateTable", handle);
        
        // Define the default stumbling state (ID = -1 means auto-assign)
        stateMachineManager::addState("stumbling", 0xFFFFFFFF);
        
        // Set flags for state ID 5 (stumbling's state index?) with flag 0x800 and bool true
        stateMachineManager::setStateFlags(5, 0x800, 1);
        
        // Add transition targets from stumbling state
        stateMachineManager::addTransitionTarget(10);    // to hitWall?
        stateMachineManager::addTransitionTarget(0xB);   // hitLedge
        stateMachineManager::addTransitionTarget(0xC);   // hitRailing
        stateMachineManager::setStateFlags(0xD, 1, 1);   // hitRamp flags
        stateMachineManager::addTransitionTarget(0x1A);  // unknown
        stateMachineManager::addTransitionCondition(0x1B); // hitEntity?
        stateMachineManager::addTransitionAnim(0xE);     // hitObject animation?
        
        // Add named transition links from stumbling to various hit states
        stateMachineManager::addTransitionLink("hitLedge", 0xB);
        stateMachineManager::addTransitionLink("hitRailing", 0xC);
        stateMachineManager::addTransitionLink("hitRamp", 0xD);
        stateMachineManager::addTransitionLink("hitObject", 0xE);
        stateMachineManager::addTransitionLink("hitProneEntity", 0x10);
        stateMachineManager::addTransitionLink("hitEntity", 0xF);
        stateMachineManager::addTransitionLink("hitWall", 10);
        stateMachineManager::addTransitionLink("hitDefault", 7); // DAT_00d63ba4
        
        // Define the hitLedge state
        stateMachineManager::addState("hitLedge", 0xFFFFFFFF);
        stateMachineManager::addTransitionTarget(0x17);
        stateMachineManager::addTransitionTarget(0x18);
        stateMachineManager::setStateFlags(0xF, 0, 1);
        stateMachineManager::addAnimEvent(0x81CFD529, 1, 1, 0, 1.0f); // animation hash with blend parameters
        stateMachineManager::setStateAnim(0xF, 1, 1);
        stateMachineManager::addTransitionCondition(0x11);
        stateMachineManager::addTransitionCondition(0x19);
        stateMachineManager::addTransitionLink("hitDefault", 0x11);
        stateMachineManager::addTransitionLink("hitDefault", 7);
        
        // Define the hitRailing state
        stateMachineManager::addState("hitRailing", 0xFFFFFFFF);
        stateMachineManager::addTransitionTarget(0x17);
        stateMachineManager::setStateFlags(0xF, 0, 1);
        stateMachineManager::addAnimEvent(0x81CFD529, 1, 1, 0, 1.0f);
        stateMachineManager::addTransitionCondition(0x12);
        stateMachineManager::setStateAnim(0xF, 1, 1);
        stateMachineManager::addTransitionLink("hitDefault", 7);
        
        // Define the hitRamp state
        stateMachineManager::addState("hitRamp", 0xFFFFFFFF);
        stateMachineManager::addTransitionTarget(0x12);
        stateMachineManager::addTransitionTarget(0x16);
        stateMachineManager::addAnimEvent(0x76AB6C71, 1, 1, 0, 1.0f); // different animation hash
        stateMachineManager::addTransitionLink("hitDefault", 7);
        
        // Define the hitObject state
        stateMachineManager::addState("hitObject", 0xFFFFFFFF);
        stateMachineManager::addTransitionTarget(0x12);
        stateMachineManager::addTransitionTarget(0x16);
        stateMachineManager::addTransitionTarget(0x10);
        stateMachineManager::addAnimEvent(0x3517CB82, 1, 1, 0, 1.0f);
        stateMachineManager::addTransitionLink("hitDefault", 7);
        
        // Define the hitProneEntity state
        stateMachineManager::addState("hitProneEntity", 0xFFFFFFFF);
        stateMachineManager::setStateFlags(0x14, 1, 1);
        stateMachineManager::addTransitionTarget(0x13);
        stateMachineManager::addTransitionTarget(0x12);
        stateMachineManager::addAnimEvent(0x81CFD529, 1, 1, 0, 1.0f);
        stateMachineManager::setStateAnim(0x14, 0, 1);
        stateMachineManager::addTransitionLink("hitDefault", 7);
        
        // Define the hitEntity state
        stateMachineManager::addState("hitEntity", 0xFFFFFFFF);
        stateMachineManager::addTransitionTarget(0x13);
        stateMachineManager::addTransitionTarget(0x12);
        stateMachineManager::addTransitionTarget(0x16);
        stateMachineManager::addAnimEvent(0x3517CB82, 1, 1, 0, 1.0f);
        stateMachineManager::addTransitionLink("hitDefault", 7);
        
        // Define the hitWall state
        stateMachineManager::addState("hitWall", 0xFFFFFFFF);
        stateMachineManager::addTransitionTarget(0x12);
        stateMachineManager::addTransitionTarget(0x16);
        stateMachineManager::addTransitionTarget(0x10);
        stateMachineManager::addAnimEvent(0x76AB6C71, 1, 1, 0, 1.0f);
        stateMachineManager::addTransitionLink("hitDefault", 7);
        
        // Define the generic hitDefault state (DAT_00d63ba4 probably "hitDefault")
        stateMachineManager::addState("hitDefault", 0xFFFFFFFF);
        stateMachineManager::addTransitionTarget(0x15);
        stateMachineManager::setStateFlags(0xD, 0, 1);
        stateMachineManager::addTransitionTarget(2);
        
        // Add a callback transition for the state machine
        stateMachineManager::addTransitionCallback(0xDEA4F75C, &LAB_00753e40, "StumbleSM");
        
        // Finalize the state machine compilation
        stateMachineManager::finalizeStateMachine();
    }
}