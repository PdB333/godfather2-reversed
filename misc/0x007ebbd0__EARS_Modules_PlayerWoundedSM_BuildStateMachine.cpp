// Xbox PDB: EARS_Modules_PlayerWoundedSM_BuildStateMachine
// FUNC_NAME: PlayerWoundedSM::setupStates
void PlayerWoundedSM::setupStates() {
    // Create or lookup the state machine by name.
    // thunk_FUN_004dafd0 likely returns a handle or pointer to the state machine instance.
    uint32_t smHandle = thunk_FUN_004dafd0("PlayerWoundedSM");
    
    // FUN_00621530 checks if the state machine already exists (returns 0 if it doesn't).
    if (FUN_00621530(smHandle) == 0) {
        // Allocate a new state machine instance.
        uint32_t newSm = FUN_009c8f80();
        
        // Register the state machine with the name.
        FUN_004ad9d0("PlayerWoundedSM", newSm);
        
        // Set default state: "wounded" with no specific transition (0xFFFFFFFF means "any" or "global").
        FUN_004adae0("wounded", 0xFFFFFFFF);
        
        // Add states with specific IDs and animations.
        // 0x38 = 56, likely an enum for "wounded" state
        FUN_004acf70(0x38);
        // 0x31 = 49, likely animation ID for wounded state
        FUN_004acff0(0x31);
        
        // Add transitions from specific states to state IDs.
        // "revive" -> 0x13 (19)
        FUN_004acc70("revive", 0x13);
        // "death" -> 0x16 (22)
        FUN_004acc70("death", 0x16);
        // "death" -> 0x1B (27)
        FUN_004acc70("death", 0x1B);
        // "death" -> 0x18 (24)
        FUN_004acc70("death", 0x18);
        // "death" -> 0x15 (21)
        FUN_004acc70("death", 0x15);
        // "execution" -> 0x19 (25)
        FUN_004acc70("execution", 0x19);
        
        // Set behavior for state 0x32 (50)
        FUN_004ad070(0x32);
        // Set default state "execution" (global transition)
        FUN_004adae0("execution", 0xFFFFFFFF);
        
        // Add state 0x35 (53)
        FUN_004acf70(0x35);
        // Add state 0x34 (52)
        FUN_004acf70(0x34);
        
        // Attach a sub-state machine named "grabReactStateTable" with initial state 0.
        FUN_004acf10("grabReactStateTable", 0);
        // Transition from "death" to state 1.
        FUN_004acc70("death", 1);
        
        // Set behavior for state 0x36 (54)
        FUN_004ad070(0x36);
        // Set default state "death" (global)
        FUN_004adae0("death", 0xFFFFFFFF);
        // Attach sub-state machine "playerDeathSM" starting at state 1.
        FUN_004acf10("playerDeathSM", 1);
        
        // Set default state "revive" (global)
        FUN_004adae0("revive", 0xFFFFFFFF);
        
        // Add states 0x33 (51), 0x34 (52), 0x37 (55)
        FUN_004acf70(0x33);
        FUN_004acf70(0x34);
        FUN_004acf70(0x37);
        
        // Transition "terminate" -> state 7
        FUN_004acc70("terminate", 7);
        // Set default state "terminate" (global)
        FUN_004adae0("terminate", 0xFFFFFFFF);
        // Add state 2
        FUN_004acf70(2);
        
        // Register a callback for a specific animation/event hash (0x1D7C15CB)
        // The second argument is a label address (likely a function pointer or code location)
        // The third argument is the state machine name for context.
        FUN_004adc90(0x1D7C15CB, &LAB_007ebb70, "PlayerWoundedSM");
        
        // Finalize/compile the state machine (e.g., build transition tables).
        FUN_004ada40();
    }
}