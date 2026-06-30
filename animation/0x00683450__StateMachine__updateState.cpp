// FUNC_NAME: StateMachine::updateState
undefined4 __fastcall StateMachine::updateState(int this)
{
    int *currentState;
    int stateResult;
    undefined4 newStateId;
    int *nextState;
    
    currentState = *(int **)(this + 4);
    stateResult = (**(code **)(*currentState + 0xc))(); // Call state's update function (vtable+0xC)
    
    if (stateResult != 2) {
        if (stateResult == 1) {
            (**(code **)(*currentState + 8))(); // Call state's exit function (vtable+0x8)
            return 0;
        }
        return 1; // State still running
    }
    
    // State wants to transition
    (**(code **)(*currentState + 8))(); // Call state's exit function (vtable+0x8)
    newStateId = (**(code **)(*currentState + 0x10))(); // Get next state ID (vtable+0x10)
    nextState = (int *)StateMachine::getState(newStateId); // FUN_006833d0
    if (nextState != (int *)0x0) {
        *(int **)(this + 4) = nextState; // Set new current state
        newStateId = StateMachine::initState(currentState); // FUN_00683410 - init old state?
        (**(code **)(*nextState + 4))(newStateId); // Call new state's enter function (vtable+0x4)
        return 1;
    }
    return 0; // Transition failed
}