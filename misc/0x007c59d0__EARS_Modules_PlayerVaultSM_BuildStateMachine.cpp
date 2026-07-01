// Xbox PDB: EARS_Modules_PlayerVaultSM_BuildStateMachine
// FUNC_NAME: PlayerVaultSM::initialize

void __cdecl PlayerVaultSM::initialize(void)
{
    // Create a state table for the player vault state machine
    void* stateTable = StateTable::create(); // FUN_009c8f80 - likely creates a StateTable object
    
    // Set the name of the state table
    StateTable::setName("playerVaultStateTable", stateTable); // FUN_004ad9d0
    
    // Add a state "vault" with no parent (-1 = no parent/root state)
    StateTable::addState("vault", -1); // FUN_004adae0
    
    // Add a transition: from "vault" with event 4 to ? (or set state property)
    StateTable::addStateOrTransition("vault", 4); // FUN_004acc70 - likely adds a state ID 4 or a transition
    
    // Add another state with same name? Probably mistake? Actually may be different call: set initial state?
    StateTable::addState("vault", -1); // duplicate? No, -1 might be "any" or "all" - but we keep as is
    
    // Set the initial state of "vaultStateTable" to state 1
    StateTable::setInitialState("vaultStateTable", 1); // FUN_004acf10
    
    // Add a "terminate" state with ID 1
    StateTable::addState("terminate", 1); // FUN_004acc70
    
    // Add "terminate" state with no parent (-1)
    StateTable::addState("terminate", -1); // FUN_004adae0
    
    // Set a final state (or maybe set the active state count) to 2
    StateTable::setFinalStateOrCount(2); // FUN_004acf70
    
    // Register the state machine with a unique CRC (0xa033cbab) and its update function (LAB_007c5980) and name
    StateMachine::registerStateMachine(0xa033cbab, (StateMachineUpdateFunc)0x007c5980, "PlayerVaultSM"); // FUN_004adc90
    
    // Finalize/commit the state table
    StateTable::commit(); // FUN_004ada40
}