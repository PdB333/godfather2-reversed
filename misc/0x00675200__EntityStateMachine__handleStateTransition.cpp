//FUNC_NAME: EntityStateMachine::handleStateTransition
short __fastcall EntityStateMachine::handleStateTransition(void* unused, EntityStateMachine* obj) {
    short currentState = *(short*)((char*)obj + 0x1a); // +0x1a: current state field
    *(short*)((char*)obj + 0x20) = 2;                 // +0x20: next state or action field set to 2
    if (currentState != 0 && currentState != 2 && currentState == 4) {
        return FUN_006750b0(obj);
    }
    return 0;
}