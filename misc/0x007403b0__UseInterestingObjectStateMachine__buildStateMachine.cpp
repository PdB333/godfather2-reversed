// FUNC_NAME: UseInterestingObjectStateMachine::buildStateMachine
// Address: 0x007403b0
// Role: Builds and registers the state machine for using interesting objects (e.g., hacking, lifting, interacting)
void UseInterestingObjectStateMachine::buildStateMachine(void)
{
    uint32_t stateMachineId;
    
    // Get a unique ID from the state machine manager
    stateMachineId = StateMachineManager::getNextId();
    // Register the state machine with its name
    StateMachineManager::registerStateMachine("UseInterestingObjectST", stateMachineId);
    // Set initial state to "gatherInit" with no flags
    StateMachineManager::setInitialState("gatherInit", 0);
    // Add state with ID 12 (0xc) - likely a base state
    StateMachineManager::addState(0xc);
    // Set transition flags: from state 5, mask 0x300000, enable 1
    StateMachineManager::setTransitionFlags(5, 0x300000, 1);
    // Define "terminate" state with ID 18 (0x12)
    StateMachineManager::addState("terminate", 0x12);
    // Define another "terminate" state with ID 19 (0x13)
    StateMachineManager::addState("terminate", 0x13);
    // Define "WaitForAnimLoad" state with ID 33 (0x21)
    StateMachineManager::addState("WaitForAnimLoad", 0x21);
    // Define "ReachedObject" state with ID 20 (0x14)
    StateMachineManager::addState("ReachedObject", 0x14);
    // Define "PathToIO" state with ID 4
    StateMachineManager::addState("PathToIO", 4);
    // Set initial state for "PathToIO" to state 1
    StateMachineManager::setInitialState("PathToIO", 1);
    // Set transition flags: from state 3, mask 0x20, enable 1
    StateMachineManager::setTransitionFlags(3, 0x20, 1);
    // Set state table "FollowPathST" with ID 1
    StateMachineManager::setStateTable("FollowPathST", 1);
    // Add "terminate" states for various exit conditions
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("terminate", 0x1b);
    // Add transition from "terminate" with event 6, mask 0x100000, enable
    StateMachineManager::addTransition("terminate", 6, 0x100000, 1);
    StateMachineManager::addState("terminate", 0x20);
    // Add pathing failure transition
    StateMachineManager::addTransition("pathingFailure", 6, 0x20, 1);
    // "ReachedObject" states
    StateMachineManager::addState("ReachedObject", 0x14);
    StateMachineManager::addState("ReachedObject", 1);
    // Set transition priority: from state 4, mask 0x20, enable
    StateMachineManager::setTransitionPriority(4, 0x20, 1);
    // Initial state for "ReachedObject" to state 2
    StateMachineManager::setInitialState("ReachedObject", 2);
    // Add state 12 again (maybe a shared state)
    StateMachineManager::addState(0xc);
    // Orientation states
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("OrientToObjectDir", 0x18);
    StateMachineManager::addState("OrientToObject", 0x15);
    StateMachineManager::addState("OrientToObjectDir", 0x16);
    StateMachineManager::addState("OrientToTarget", 0x17);
    StateMachineManager::addState("WaitForAnimLoad", 4);
    // Set initial for "OrientToObject" to state 3
    StateMachineManager::setInitialState("OrientToObject", 3);
    StateMachineManager::setStateTable("turnToPositionTerminateTable", 1);
    // Terminate and pathing failure for orientation
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("terminate", 0x1b);
    StateMachineManager::addTransition("terminate", 6, 0x100000, 1);
    StateMachineManager::addState("WaitForAnimLoad", 1);
    StateMachineManager::setInitialState("OrientToTarget", 4);
    StateMachineManager::setStateTable("turnToPositionTerminateTable", 1);
    // Repeat for "OrientToObjectDir" and "WaitForAnimLoad"
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("terminate", 0x1b);
    StateMachineManager::addTransition("terminate", 6, 0x100000, 1);
    StateMachineManager::addState("WaitForAnimLoad", 1);
    StateMachineManager::setInitialState("OrientToObjectDir", 5);
    StateMachineManager::setStateTable("turnToPositionTerminateTable", 1);
    // Another orientation block (possibly "OrientToObjectDir" with different event)
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("terminate", 0x1b);
    StateMachineManager::addTransition("terminate", 6, 0x100000, 1);
    StateMachineManager::addState("WaitForAnimLoad", 1);
    StateMachineManager::setInitialState("WaitForAnimLoad", 6);
    // Add state 41 (0x29)
    StateMachineManager::addState(0x29);
    // Holster weapon states
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("terminate", 0x1b);
    StateMachineManager::addTransition("terminate", 6, 0x100000, 1);
    StateMachineManager::addState("TestHolsterWeapon", 0x19);
    // Add transition with data from global
    StateMachineManager::addTransitionWithData("terminate", 2, DAT_00d5eee4, 1);
    StateMachineManager::setInitialState("TestHolsterWeapon", 7);
    StateMachineManager::addState(0x32);
    // Holster weapon continuation
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("terminate", 0x1b);
    StateMachineManager::addTransition("terminate", 6, 0x100000, 1);
    StateMachineManager::addState("HolsterWeapon", 0x23);
    StateMachineManager::addState("StartUsingAnimation", 4);
    StateMachineManager::setInitialState("HolsterWeapon", 8);
    StateMachineManager::setStateTable("HolsterGunST", 1);
    // Use interaction states
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("terminate", 0x1b);
    StateMachineManager::addTransition("terminate", 6, 0x100000, 1);
    StateMachineManager::addState("StartUsingAnimation", 1);
    StateMachineManager::setInitialState("StartUsingAnimation", 9);
    StateMachineManager::addState(0x27);
    StateMachineManager::addState(0x24);
    StateMachineManager::addState(0x2d);
    StateMachineManager::addState(0x31);
    StateMachineManager::addState(0x2d);
    // Set exit action for state 0x2d (maybe anim finished)
    StateMachineManager::setStateExitAction(0x2d);
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("ResetBodyAnimation", 0x1a);
    StateMachineManager::addState("finishedUsing", 0x13);
    StateMachineManager::addState("finishedUsing", 0x1b);
    StateMachineManager::addTransition("finishedUsing", 6, 0x100000, 1);
    StateMachineManager::addState("finishedUsing", 0x22);
    StateMachineManager::addState("InteractWithObject", 0x1c);
    StateMachineManager::setInitialState("InteractWithObject", 10);
    StateMachineManager::addState(0x2f);
    StateMachineManager::addState(0x23);
    StateMachineManager::addState(0x26);
    StateMachineManager::addState(0x31);
    StateMachineManager::addState(0x2d);
    StateMachineManager::setStateExitAction(0x2d);
    StateMachineManager::setStateExitAction(0x2e);
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("ResetBodyAnimation", 0x1a);
    StateMachineManager::addState("finishedUsing", 0x13);
    StateMachineManager::addState("finishedUsing", 0x1b);
    StateMachineManager::addTransition("finishedUsing", 6, 0x100000, 1);
    StateMachineManager::addState("finishedUsing", 0x22);
    StateMachineManager::addState("finishedUsing", 0x20);
    StateMachineManager::addState("finishedUsing", 0x1f);
    StateMachineManager::addState("ApplyMotivesAndStartAgain", 0x1e);
    StateMachineManager::setInitialState("ApplyMotivesAndStartAgain", 0xb);
    StateMachineManager::addState(0x2b);
    StateMachineManager::addState(0x30);
    StateMachineManager::addState("InteractWithObject", 4);
    StateMachineManager::setInitialState("finishedUsing", 0xc);
    // Final transitions and state setup
    StateMachineManager::setTransitionFlags(4, 0x300000, 1);
    StateMachineManager::addState(0x25);
    StateMachineManager::addState(0x2d);
    StateMachineManager::setStateExitAction(0x2d);
    StateMachineManager::addState("terminate", 0x12);
    StateMachineManager::addState("ResetBodyAnimation", 0x1a);
    StateMachineManager::addState("terminate", 0x1d);
    StateMachineManager::setStateAction(0x28);
    StateMachineManager::setInitialState("ResetBodyAnimation", 0xd);
    StateMachineManager::addState(0x2a);
    StateMachineManager::addState("terminate", 4);
    StateMachineManager::setInitialState("pathingFailure", 0xe);
    StateMachineManager::addState(0x2c);
    StateMachineManager::addState(2);
    StateMachineManager::setInitialState("terminate", 0xf);
    StateMachineManager::addState(2);
    // Finalize the state machine with a hash and callback address
    StateMachineManager::buildAndRegisterStateMachine(0x717ceaca, &UseInterestingObjectStateMachine::handleEvent, "UseInterestingObjectSM");
    // Clean up or return
    StateMachineManager::finalize();
    return;
}