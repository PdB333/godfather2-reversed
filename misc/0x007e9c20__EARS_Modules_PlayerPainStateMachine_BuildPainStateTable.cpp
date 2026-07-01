// Xbox PDB: EARS_Modules_PlayerPainStateMachine_BuildPainStateTable
// FUNC_NAME: PlayerPainStateMachine::initializePainStateTable
void PlayerPainStateMachine::initializePainStateTable(void)
{
    int iVar2;
    int tableHandle;
    
    // Get or create the pain state table
    tableHandle = thunk_FUN_004dafd0("PlayerPainStateTable");
    iVar2 = FUN_00621530(tableHandle);
    
    if (iVar2 == 0) {
        // Table doesn't exist yet, create and populate it
        tableHandle = FUN_009c8f80();
        FUN_004ad9d0("PlayerPainStateTable", tableHandle);
        
        // State: painInit (initial pain state)
        FUN_004adae0("painInit", 0xffffffff);  // Set as default state
        FUN_004acf70(0x36);                     // Set state ID
        FUN_004ad0f0(5, 1, 1);                  // Set transition parameters
        FUN_004acc70("is_wounded", 0x15);       // Add transition to wounded
        FUN_004acc70("death", 0xc);             // Add transition to death
        FUN_004acd20("knockedDown", 0x14, 4, 1); // Add transition to knocked down
        FUN_004acd20("ground_hit", 0x10, 3, 1); // Add transition to ground hit
        FUN_004acd20("crawl_hit", 0x10, 2, 1);  // Add transition to crawl hit
        FUN_004acd20("kneel_hit", 0x10, 1, 1);  // Add transition to kneel hit
        FUN_004acd20("kneel_hit", 0x10, 4, 1);  // Another kneel hit transition
        FUN_004acd20("stand_hit", 0x10, 0, 1);  // Add transition to stand hit
        FUN_004acc70("terminate", 4);            // Add terminate transition
        
        // State: is_wounded
        FUN_004adae0("is_wounded", 0xffffffff);  // Set as default state
        FUN_004ad0f0(0x2c, 1, 1);                // Set transition parameters
        FUN_004ad170(0x2d, 1, 1);                // Set additional transition
        FUN_004acf70(0x3a);                      // Set state ID
        FUN_004acff0(8);                         // Set animation
        FUN_004acc70("terminate", 0x17);         // Add terminate transition
        FUN_004acc70("terminate", 7);            // Another terminate
        FUN_004acc70("terminate", 0x16);         // Another terminate
        
        // State: death
        FUN_004adae0("death", 0xffffffff);       // Set as default state
        FUN_004ad0f0(0x2c, 1, 1);                // Set transition parameters
        FUN_004ad170(0x2d, 1, 1);                // Set additional transition
        FUN_004acf70(0x35);                      // Set state ID
        FUN_004acff0(8);                         // Set animation
        FUN_004acc70("terminate", 7);            // Add terminate transition
        FUN_004acc70("terminate", 0x16);         // Another terminate
        
        // State: stand_hit
        FUN_004adae0("stand_hit", 0xffffffff);   // Set as default state
        FUN_004acf70(0x38);                      // Set state ID
        FUN_004acf70(0x33);                      // Set additional state
        FUN_004acff0(8);                         // Set animation
        FUN_004acd20("painInit", 6, 1, 1);       // Add transition back to painInit
        FUN_004acc70("terminate", 0x13);         // Add terminate transition
        FUN_004acc70("terminate", 7);            // Another terminate
        
        // State: knockedDown
        FUN_004adae0("knockedDown", 0xffffffff); // Set as default state
        FUN_004ad0f0(0x2c, 1, 1);                // Set transition parameters
        FUN_004ad170(0x2d, 1, 1);                // Set additional transition
        FUN_004acf70(0x34);                      // Set state ID
        FUN_004acff0(8);                         // Set animation
        FUN_004ad170(0x32, 8, 1);                // Set additional transition
        FUN_004acc70("terminate", 7);            // Add terminate transition
        
        // State: crawlToGround
        FUN_004adae0("crawlToGround", 0xffffffff); // Set as default state
        FUN_004ace70(0x6d4224e5, 1, 1, 0, 0x3f800000); // Set blend parameters
        FUN_004acff0(8);                         // Set animation
        FUN_004acc70("terminate", 7);            // Add terminate transition
        
        // State: kneelToGround
        FUN_004adae0("kneelToGround", 0xffffffff); // Set as default state
        FUN_004ace70(0xbf5e4f87, 1, 1, 0, 0x3f800000); // Set blend parameters
        FUN_004ad0f0(0x2c, 1, 1);                // Set transition parameters
        FUN_004ad170(0x2d, 1, 1);                // Set additional transition
        FUN_004acff0(8);                         // Set animation
        FUN_004acc70("terminate", 7);            // Add terminate transition
        
        // State: ground_hit
        FUN_004adae0("ground_hit", 0xffffffff);  // Set as default state
        FUN_004acf70(0x38);                      // Set state ID
        FUN_004acf70(0x33);                      // Set additional state
        FUN_004acff0(8);                         // Set animation
        FUN_004acc70("terminate", 0x13);         // Add terminate transition
        FUN_004acc70("terminate", 7);            // Another terminate
        
        // State: kneel_hit
        FUN_004adae0("kneel_hit", 0xffffffff);   // Set as default state
        FUN_004acf70(0x38);                      // Set state ID
        FUN_004acf70(0x33);                      // Set additional state
        FUN_004acff0(8);                         // Set animation
        FUN_004acd20("kneelToGround", 0xe, 4, 1); // Add transition to kneelToGround
        FUN_004acd20("kneel_hit", 6, 1, 1);      // Add self-transition
        FUN_004acc70("terminate", 0x13);         // Add terminate transition
        FUN_004acc70("terminate", 7);            // Another terminate
        
        // State: crawl_hit
        FUN_004adae0("crawl_hit", 0xffffffff);   // Set as default state
        FUN_004acf70(0x38);                      // Set state ID
        FUN_004acf70(0x33);                      // Set additional state
        FUN_004acff0(8);                         // Set animation
        FUN_004acd20("crawlToGround", 0xe, 4, 1); // Add transition to crawlToGround
        FUN_004acd20("crawl_hit", 6, 1, 1);      // Add self-transition
        FUN_004acc70("terminate", 0x13);         // Add terminate transition
        FUN_004acc70("terminate", 7);            // Another terminate
        
        // State: terminate
        FUN_004adae0("terminate", 0xffffffff);   // Set as default state
        FUN_004acf70(0x37);                      // Set state ID
        FUN_004acf70(0x38);                      // Set additional state
        FUN_004acf70(2);                         // Set another state
        FUN_004adc90(0x3a36526d, &LAB_007e9bd0, "PlayerPainStateMachine"); // Register callback
        FUN_004ada40();                          // Finalize table
    }
    return;
}