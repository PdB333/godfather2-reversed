// FUNC_NAME: StateMachine::update
// Address: 0x00683450
// Role: Updates the current state, handles state transitions. The machine holds a pointer to a State object at offset +0x04.
// State virtual function table offsets:
//   +0x04: init(void*)
//   +0x08: execute()
//   +0x0C: getStateID() -> int
//   +0x10: getNextResource() -> void*

// Forward declarations for helper functions called at 0x006833d0 and 0x00683410
extern State* createStateFromResource(void* resource);
extern void* prepareStateForTransition(State* oldState);

int __fastcall StateMachine::update(void* thisPtr) {
    State* currentState = *(State**)((char*)thisPtr + 4);
    int stateID = currentState->getStateID();

    if (stateID != 2) {
        if (stateID == 1) {
            currentState->execute();
            return 0;
        }
        return 1;
    }

    // State 2 indicates a transition is needed
    currentState->execute();
    void* resource = currentState->getNextResource();
    State* newState = createStateFromResource(resource);
    if (newState != nullptr) {
        *(State**)((char*)thisPtr + 4) = newState; // +0x04
        void* arg = prepareStateForTransition(currentState);
        newState->init(arg);
        return 1;
    }
    return 0;
}