// Xbox PDB: EARS::Modules::NPCVaultSM::BuildStateMachine
// FUNC_NAME: NPCVaultStateMachine::initialize
void NPCVaultStateMachine::initialize(void)
{
    // Get a state machine manager instance (likely singleton)
    void* stateMachine = getStateMachineManager();

    // Set the state machine name to "NPCVaultST"
    setStateMachineName(stateMachine, "NPCVaultST");

    // Add a null transition from state index 0? (DAT_00d63420 might be a global state ID)
    addTransition(&DAT_00d63420, 0);

    // Add state with ID 0x12 (18)
    addState(0x12);

    // Add states with names and timeout/action IDs
    addNamedState("approachVault", 10);
    addNamedState("preVault", 4);

    // Add transition from "approachVault" to state 1
    addTransition("approachVault", 1);

    // Set initial state to "SeekToPositionST" with parameter 1
    setInitialState("SeekToPositionST", 1);

    addNamedState("preVault", 1);
    addTransition("preVault", 2);
    addNamedState("vault", 0xC); // 12
    addNamedState("vaultWait", 4);
    addTransition("vaultWait", 3);

    // Add states with IDs 0x13, 8
    addState(0x13);
    addState(8);

    // Set some state property (maybe an animation or action) for state 8
    setStateAction(8);

    addNamedState("vault", 0xC);
    addNamedState("vaultFailed", 0xE); // 14

    // Transition from "vault" to state -1 (likely default/exit)
    addTransition("vault", 0xFFFFFFFF);

    addState(0x15);
    setInitialState("VaultStateTable", 1);
    addNamedState("completedVault", 1);

    // Set state action for state 0x16 (22)
    setStateAction(0x16);

    addTransition("completedVault", 5);
    addNamedState("vaultFailed", 0xD); // 13
    addNamedState("gotoFinalPos", 0xB); // 11
    addNamedState("terminate", 4);
    addTransition("gotoFinalPos", 6);
    setInitialState("SeekToPositionST", 1);
    addNamedState("terminate", 1);
    addTransition("vaultFailed", 7);
    addState(0x14); // 20
    addNamedState("terminate", 4);
    addTransition("terminate", 0xFFFFFFFF);
    addState(2);

    // Register the state machine with a name and a function table (likely virtual method table)
    registerStateMachine("NPCVaultSM", (void*)&LAB_0074bbd0);

    // Finalize or cleanup
    finalizeStateMachine();
}