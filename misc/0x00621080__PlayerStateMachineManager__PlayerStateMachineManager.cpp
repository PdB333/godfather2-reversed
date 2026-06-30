// FUNC_NAME: PlayerStateMachineManager::PlayerStateMachineManager

// Reconstructed constructor for a class that holds two state machine sub-objects
// and a state component. The class is likely part of the Player FSM system.
// Address: 0x00621080

PlayerStateMachineManager * __thiscall PlayerStateMachineManager::PlayerStateMachineManager(
    PlayerStateMachineManager *this,
    int someIndex1,                    // param_2: likely state machine identifier
    int someIndex2,                    // param_3: another index
    int *parentDelegate,               // param_4: pointer to parent object interface
    undefined4 someParam)              // param_5: extra data
{
    int *piVar1;
    undefined4 uVar2;
    PlayerStateMachineManager *thisPtr;
    int tempResult;
    bool isNull;
    int initStack[4];      // used to pass initialization parameters to sub-object constructor
    
    // Store singleton reference
    DAT_012234ac = this;
    
    // Setup vtable for this object
    *this = &PTR_FUN_00e414d8;
    
    // Store the parent delegate (interface pointer)
    this->parentDelegate = parentDelegate;
    
    // Call virtual function on parent delegate (offset 8 = some init method)
    (**(code **)(*parentDelegate + 8))();
    
    // Prepare initialization parameters for state machine component
    initStack[0] = 0x18;       // possibly size or mode
    initStack[1] = 4;          // parameter
    initStack[2] = 0x28;       // another parameter
    initStack[3] = 4;          // yet another parameter
    
    // The actual indices passed originally are stored but not used directly?
    // They might be passed to the sub-object via stack later
    int idx1 = someIndex2 + 1;
    int idx2 = someIndex1 + 1;
    
    // Store the input parameter at offset 5
    this->field_5 = someParam;
    
    // Create the state machine component (size 0x1c = 28 bytes)
    piVar1 = (int *)FUN_0066f240();                          // allocate something?
    uVar2 = FUN_009c8e80(piVar1);                            // possibly a memory pool allocation
    this->stateMachineComponent = uVar2;
    
    // Allocate the state component object
    undefined4 *stateComponent = (undefined4 *)FUN_009c8e50(0x1c);
    if (stateComponent != (undefined4 *)0x0) {
        *stateComponent = &PTR_LAB_00e414c4;                 // set vtable
        FUN_0066f290(&initStack);                            // initialize with the parameters
        stateComponent[6] = 1;                                // set some flag
        stateComponent[5] = 0;                                // another field
    }
    this->stateComponent = stateComponent;
    
    // --- First sub-object allocation (size 0x24 = 36 bytes) ---
    int subObjA = FUN_009c8e50(0x24);
    isNull = (subObjA == 0);
    if (subObjA != 0) {
        // Use a local array to pass zero-initialized parameters
        int zeroParams[3] = {0, 0, 0};
        int *parentComp = (int *)this->stateComponent;
        // Call virtual on state component + 8 (some getter)
        (**(code **)(*parentComp + 8))();
        // Create sub-object with these parameters and the component
        tempResult = FUN_004265d0(zeroParams, parentComp);
        // Call constructor for sub-object type A
        FUN_00622570();
    }
    this->subStateMachineA = subObjA;
    
    // Cleanup if allocation succeeded
    if (!isNull) {
        if (tempResult != 0) {
            (**(code **)(*parentComp + 4))(tempResult, 0);   // release temp?
        }
        (**(code **)(*parentComp + 0xc))();                  // finalize
    }
    
    // --- Second sub-object allocation (same size 0x24) ---
    int subObjB = FUN_009c8e50(0x24);
    isNull = (subObjB == 0);
    if (subObjB != 0) {
        int *parentComp = (int *)this->stateComponent;
        int zeroParams[3] = {0, 0, 0};
        (**(code **)(*parentComp + 8))();
        tempResult = FUN_004265d0(zeroParams, parentComp);
        // Different constructor for sub-object type B
        FUN_00622090();
    }
    this->subStateMachineB = subObjB;
    
    // Cleanup again
    if (!isNull) {
        if (tempResult != 0) {
            (**(code **)(*parentComp + 4))(tempResult, 0);
        }
        (**(code **)(*parentComp + 0xc))();
    }
    
    // Initialize field at offset 2 to 0
    this->someFlag = 0;
    
    return this;
}