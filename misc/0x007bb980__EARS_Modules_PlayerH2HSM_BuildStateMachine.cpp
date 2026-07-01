// Xbox PDB: EARS_Modules_PlayerH2HSM_BuildStateMachine
// FUNC_NAME: PlayerF2FSM::setupPlayerH2HStateTable
void __thiscall setupPlayerH2HStateTable(void)
{
    StateTableDefinition* stateTable;
    int checkResult;
    
    // Get the "playerH2HStateTable" state table by name
    stateTable = (StateTableDefinition*)thunk_FUN_004dafd0("playerH2HStateTable");
    checkResult = FUN_00621530(stateTable);
    if (checkResult == 0) {
        // Table doesn't exist yet - create and populate it
        stateTable = (StateTableDefinition*)FUN_009c8f80();
        FUN_004ad9d0("playerH2HStateTable",stateTable);
        
        // Set default state "Valid" (invalid state)
        FUN_004adae0("Valid",0xffffffff);
        
        // Add states with transitions
        // State IDs: Terminate=0x13, QuickAttackLL=0x16, QuickAttackLR=0x19, etc.
        FUN_004acf70(0x42);  // Create state 0x42
        FUN_004ad0f0(0x12,0,1);  // Set animation data
        FUN_004acc70("Terminate",0x13);  // Add transition to Terminate
        
        // --- QuickAttackLL ---
        FUN_004acd20("QuickAttackLL",0x21,0x8000016,1);
        // --- QuickAttackLR ---
        FUN_004acd20("QuickAttackLR",0x21,0x10000019,1);
        // ... (additional state definitions follow the same pattern)
        // Set transition table for "QuickAttackL" with input mappings
        FUN_004adae0("QuickAttackL",0xffffffff);
        FUN_004ad0f0(0x12,0,1);  // Animation setup
        
        // Transition logic: inputs 0x37, 0x32, 0x33, 0x34, etc. map to states
        FUN_004ad0f0(0x37,0,1);
        FUN_004ad0f0(0x32,0,1);
        FUN_004ad0f0(0x33,0,1);
        FUN_004ad0f0(0x34,0,1);
        FUN_004acf70(0x35);
        FUN_004acf70(0x3a);
        FUN_004ad0f0(0x38,0,1);
        FUN_004ad070(0x26);
        FUN_004ad170(0x39,0,1);
        
        // State transitions go to specific attack states
        FUN_004acc70("QuickAttackLStomp",0x14);
        FUN_004acc70("QuickAttackLMeleeStdKnlUnarmedKnl",0x15);
        FUN_004acc70("QuickAttackLL",0x16);
        // ... additional transitions
        
        // Add transition overs for combo chaining
        FUN_004adae0("QuickAttackLTrans",0xffffffff);
        // ... more transition definitions
        
        // Complete all defined combos: L->L->L, L->L->R, L->R->L, etc.
        // Each combo has its own state with transitions to next hits
        // ... (extensive combo tree definition follows)
        
        // Setup grapple state reference
        FUN_004acf10("playerGrappleStateTable",1);
        
        // Terminate states for various combo branches
        FUN_004acc70("Terminate",0xb);  // Generic terminate
        FUN_004acc70("Terminate",0x20); // Terminate on input change
        
        // Finalize state table
        FUN_004adc90(0x1d5256e,&LAB_007bb950,"PlayerH2HSM");
        FUN_004ada40();
    }
    return;
}