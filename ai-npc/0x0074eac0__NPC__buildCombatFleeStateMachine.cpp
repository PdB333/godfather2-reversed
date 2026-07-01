// FUNC_NAME: NPC::buildCombatFleeStateMachine
// Address: 0x0074eac0
// Purpose: Constructs the combat flee state machine for NPC off-path fleeing behavior.
// The function registers states and transitions for the "combatFleeSM" state machine,
// then finalizes it as "OffPathFleeStateMachine" with a function pointer at LAB_0074e560.

extern float DAT_00e44620; // +0x?? global delay/weight factor
extern int DAT_00d5779c;   // +0x?? global condition flag

// Forward declarations of internal state machine helper functions
static void* GetStateMachineManager(void); // FUN_009c8f80
static void RegisterStateMachine(const char* name, void* manager); // FUN_004ad9d0
static void SetDefaultState(const char* stateName, int stateId); // FUN_004adae0 (stateId -1 means no default?)
static void AddState(int stateId); // FUN_004acf70
static void AddTransition(int fromState, int toState, int condition); // FUN_004ad170 (condition flags?)
static void AddState(const char* stateName, int stateId); // FUN_004acc70
static void SetStateTable(const char* tableName, int tableId); // FUN_004acf10
static void AddTransitionWithCondition(const char* fromState, int transitionId, int condition, int unk); // FUN_004acd20
static void AddTransitionWithDelay(const char* fromState, int transitionId, float delay, int unk); // FUN_004acd80
static void AddStateShort(int stateId); // FUN_004ad070 (shorter version?)
static void AddSomething(int id); // FUN_004acff0 (unclear, could be state or transition)
static void FinalizeStateMachine(uint hash, void* funcPtr, const char* name); // FUN_004adc90
static void StateMachineCleanup(void); // FUN_004ada40

void NPC::buildCombatFleeStateMachine(void)
{
    void* manager;
    
    manager = GetStateMachineManager();
    RegisterStateMachine("combatFleeSM", manager);
    
    // --- Initial state setup ---
    SetDefaultState("offpathFleeInit", -1); // -1 indicates no previous state
    AddState(0x13);                         // state ID 0x13
    AddTransition(5, 0x4020, 1);           // from 5 to 0x4020 with condition 1
    
    // ---- States for seeking flee nodes ----
    AddState("terminate", 0x10);
    AddState("preSeekToFleeNode", 0x0f);
    AddState("seekToCoverNode", 0x11);
    AddState("fleeTowardsAnyGraph", 4);
    SetDefaultState("preSeekToFleeNode", -1); // re-set default? or transition?
    AddState("turnTowards", 0x0e);
    AddState("seekToFleeNode", 4);
    SetDefaultState("seekToFleeNode", -1);
    SetStateTable("FollowPathST", 1);
    AddState("fleeTowardsAnyGraph", 0x1f);
    AddTransitionWithCondition("fleeToFleeFailed", 6, 0x4000, 1);
    AddState("terminate", 0x0a);             // another terminate state?
    AddTransitionWithDelay("fleeTowardsAnyGraph", 0x20, DAT_00e44620, 1);
    AddState("turnTowards", 0x17);
    AddState("turnTowards", 1);
    AddStateShort(0x23);
    SetDefaultState("fleeToFleeFailed", -1);
    AddState(0x25);
    AddState("preCower", 4);
    SetDefaultState("seekToCoverNode", -1);
    SetStateTable("FollowPathST", 1);
    AddState("terminate", 0x0b);
    AddState("preCower", 0x0d);
    AddState("fleeTowardsAnyGraph", 0x1f);
    AddTransitionWithCondition("fleeToCoverFailed", 6, 0x4000, 1);
    AddTransitionWithDelay("fleeTowardsAnyGraph", 0x20, DAT_00e44620, 1);
    AddState("preCower", 0x17);
    AddState("preCower", 1);
    AddStateShort(0x23);
    SetDefaultState("fleeToCoverFailed", -1);
    AddState(0x24);
    AddState("preCower", 4);
    SetDefaultState("turnTowards", -1);
    AddState(0x0c);
    AddState(0x0d);
    SetStateTable("turnToEntityTerminateTable", 1);
    
    // ---- Action and recovery states ----
    AddState("performAction", 0x14);
    AddState("fleeOnGraph", 0x19);
    AddState("preCower", 1);
    AddState("terminate", 0x0a);
    SetDefaultState("performAction", -1);
    AddState(0x12);
    AddSomething(8);
    AddSomething(0x14);
    AddStateShort(0x15);
    AddState("recover", 7);
    SetDefaultState("recover", -1);
    AddState(0x1f);
    SetStateTable("recoverStateTable", 0);
    AddState("fleeOnGraph", 0x19);
    AddState("preCower", 1);
    SetDefaultState("fleeOnGraph", -1);
    AddState(0x16);
    AddState("terminate", 4);
    SetDefaultState("fleeTowardsAnyGraph", -1);
    AddState(0x20);
    
    // ---- Random flee states ----
    AddState("fleeRandom", 0x1d);
    AddState("fleeTowardsAnyGraph2", 4);
    SetDefaultState("fleeTowardsAnyGraph2", -1);
    SetStateTable("FollowPathST", 1);
    AddTransitionWithDelay("fleeRandom", 0x20, DAT_00e44620, 1);
    AddState("fleeRandom", 0x1d);
    AddState("fleeRandom", 0x1f);
    AddState("preCower", 0x17);
    AddState("preCower", 1);
    AddStateShort(0x23);
    SetDefaultState("fleeRandom", -1);
    AddState(0x21);
    SetStateTable("FollowPathST", 1);
    AddState("preCower", 0x17);
    AddState("fleeRandomFailed", 0x1f);
    AddState("preCower", 1);
    AddTransitionWithDelay("preCower", 0x20, DAT_00e44620, 1);
    AddStateShort(0x22);
    AddStateShort(0x23);
    SetDefaultState("fleeRandomFailed", -1);
    AddState(0x27);
    AddState("preCower", 4);
    SetDefaultState("preCower", -1);
    AddState("combatCower", 4);
    SetDefaultState("combatCower", -1);
    AddState(0x19);
    AddSomething(0x1e);
    AddState("offpathFleeInit", 0x1c);
    AddTransitionWithDelay("terminate", 2, (float)DAT_00d5779c, 1); // condition as float?
    AddState("terminate", 0x21);
    AddStateShort(0x1d);
    SetDefaultState("terminate", -1);
    AddState(2); // final state ID
    
    // Finalize the state machine with a unique hash and a function pointer
    FinalizeStateMachine(0x996586b0, &LAB_0074e560, "OffPathFleeStateMachine");
    StateMachineCleanup();
    return;
}