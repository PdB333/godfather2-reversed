// Xbox PDB: EARS_Modules_PlayerGrappleSM_BuildStateMachineMultiplayerExecute
// FUNC_NAME: AnimationDatabase::registerStandardGrapples
void AnimationDatabase::registerStandardGrapples(void)
{
    // Register animation set 0x35 (base grapples)
    FUN_004acf70(0x35);
    
    // Register edge/ledge grapples with states
    FUN_004ad0f0(0x20,0x3f,1); // Grab edge, state 0x3f, enabled
    FUN_004ad0f0(0x22,2,1);     // Grab high ledge, state 2, enabled
    FUN_004ad0f0(0x12,0,1);     // Grab low ledge, state 0, enabled
    
    // Register grab end transition with pointer data
    FUN_004ad1b0(0x2e,_DAT_00d5c458,1); // GrabEnd transition, global data, enabled
    
    // Register unarmed grab end
    FUN_004ad070(0x2f);
    
    // Register specific grab sequences with names
    FUN_004acc70("GrabEnd",0x13);        // Unarmed grab end
    FUN_004acc70("Execution",0x4e);      // Execution animation (front)
    FUN_004acc70("Execution",0x17);      // Execution animation (alternate)
    
    // Register execution variations with priority
    FUN_004acd20("Execution",0x15,1,1);  // Execution variation 1, priority 1
    FUN_004acd20("Execution",0x15,2,1);  // Execution variation 2, priority 1
    
    FUN_004acc70("Execution",0x16);      // Another execution variant
    
    FUN_004acc70("GrabBehind",0x1b);     // Behind grab animation
    
    FUN_004acc70("GrabEndPaired",4);      // Paired grab end animation
    
    return;
}