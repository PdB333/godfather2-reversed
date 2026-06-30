// FUNC_NAME: BehaviorController::setup
undefined4 __fastcall BehaviorController::setup(int this)
{
    undefined4 *memoryManagerPtr;
    int allocResult;
    undefined4 stateSetupResult;
    int *stateDataPtr;
    undefined4 initResult;
    undefined4 allocInfo[3]; // local_8, local_10, local_14
    
    memoryManagerPtr = (undefined4 *)MemoryManager::getInstance();   // FUN_009c8f80()
    allocInfo[0] = 2;       // alignment or flags
    allocInfo[1] = 0x10;    // 16 bytes overhead?
    allocInfo[2] = 0;       // additional flags?
    
    allocResult = (**(code **)(*memoryManagerPtr))(0x200, &allocInfo); // allocate 0x200 bytes for behavior data
    if (allocResult == 0) {
        stateSetupResult = 0;
    }
    else {
        stateSetupResult = BehaviorController::initStates(this); // FUN_006e0620
    }
    
    // Check if the current state is inactive (0) or a special state (0x48)
    if (*(int *)(this + 0x68) == 0 || *(int *)(this + 0x68 == 0x48)) {
        stateDataPtr = (int *)HashTable::find(*(int *)(this + 0x58), 0); // FUN_00446100, hashmap lookup by key 0
        if (stateDataPtr != (int *)0x0) {
            // Call virtual function at vtable offset 0x10 (method index 4) on the state data
            // Arguments: hash ID (0x383225a1) and pointer to allocInfo struct
            (**(code **)(*stateDataPtr + 0x10))(0x383225a1, &allocInfo);
            StateManager::registerState(0); // FUN_006d68e0
        }
        int currentState = *(int *)(this + 0x68);
        if (currentState == 0 || currentState == 0x48) {
            // Another virtual call via global manager table
            initResult = (**(code **)(*(int *)*(undefined4 **)(DAT_012233a0 + 4) + 0xc))(); // likely get current state name or config
            StateManager::registerState(initResult); // FUN_006d68e0
        }
    }
    
    StateMachine::reset(&this->0x68); // FUN_006e03b0, reset the state field
    return stateSetupResult;
}