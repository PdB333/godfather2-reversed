// Xbox PDB: EARS_Modules_BurstFireSM_BuildBurstFireStateTable
// FUNC_NAME: BurstFireSM::initialize
void BurstFireSM::initialize(void)
{
    // Get burst fire state machine parameter (likely weapon type or fire mode)
    int burstFireParam = getBurstFireParameter(); // FUN_009c8f80

    // Set initial state "BurstFireST" with the parameter
    addState("BurstFireST", burstFireParam); // FUN_004ad9d0

    // Add transition from "burstInit" to nowhere (0xFFFFFFFF = no transition)
    addTransition("burstInit", 0xFFFFFFFF); // FUN_004adae0

    // Add action for state 0x23 (35) - possibly "startBurst"
    addAction(0x23); // FUN_004acf70

    // Add timed state "shotblocked" with duration 0x14 (20)
    addTimedState("shotblocked", 0x14); // FUN_004acc70

    // Add timed state "prepFire" with duration 0x16 (22)
    addTimedState("prepFire", 0x16); // FUN_004acc70

    // Add timed state "delayFire" with duration 0x17 (23)
    addTimedState("delayFire", 0x17); // FUN_004acc70

    // Add transition from "delayFire" to nowhere
    addTransition("delayFire", 0xFFFFFFFF); // FUN_004adae0

    // Add action for state 0x28 (40)
    addAction(0x28); // FUN_004acf70

    // Add action for state 0x25 (37)
    addAction(0x25); // FUN_004acff0

    // Add timed state "prepFire" again (overwrites previous?)
    addTimedState("prepFire", 0x16); // FUN_004acc70

    // Add transition from "prepFire" to nowhere
    addTransition("prepFire", 0xFFFFFFFF); // FUN_004adae0

    // Add action for state 0x2B (43)
    addAction(0x2B); // FUN_004acf70

    // Add action for state 0x25 again
    addAction(0x25); // FUN_004acff0

    // Add timed state "playFireAnim" with duration 0x12 (18)
    addTimedState("playFireAnim", 0x12); // FUN_004acc70

    // Add transition from "playFireAnim" to nowhere
    addTransition("playFireAnim", 0xFFFFFFFF); // FUN_004adae0

    // Add action for state 0x24 (36)
    addAction(0x24); // FUN_004acf70

    // Add action for state 0x2C (44)
    addAction(0x2C); // FUN_004acf70

    // Add action for state 0x25 again
    addAction(0x25); // FUN_004acff0

    // Add timed state "doneCCTFiring" with duration 0x13 (19)
    addTimedState("doneCCTFiring", 0x13); // FUN_004acc70

    // Add timed state "doneCCTFiring" with duration 7 (overwrites?)
    addTimedState("doneCCTFiring", 7); // FUN_004acc70

    // Add transition from "doneCCTFiring" to nowhere
    addTransition("doneCCTFiring", 0xFFFFFFFF); // FUN_004adae0

    // Add action for state 0x27 (39)
    addAction(0x27); // FUN_004acf70

    // Add action for state 0x25 again
    addAction(0x25); // FUN_004acff0

    // Add timed state "postFireDelay" with duration 0x15 (21)
    addTimedState("postFireDelay", 0x15); // FUN_004acc70

    // Add timed state "fireGun" with duration 0x16 (22)
    addTimedState("fireGun", 0x16); // FUN_004acc70

    // Add transition from "fireGun" to nowhere
    addTransition("fireGun", 0xFFFFFFFF); // FUN_004adae0

    // Add action for state 0x26 (38)
    addAction(0x26); // FUN_004acf70

    // Add action for state 0x27 again
    addAction(0x27); // FUN_004acf70

    // Add action for state 0x25 again
    addAction(0x25); // FUN_004acff0

    // Add timed state "postFireDelay" again
    addTimedState("postFireDelay", 0x15); // FUN_004acc70

    // Add timed state "fireGun" again
    addTimedState("fireGun", 0x16); // FUN_004acc70

    // Add transition from "shotblocked" to nowhere
    addTransition("shotblocked", 0xFFFFFFFF); // FUN_004adae0

    // Add actions for states 0x29, 0x2A, 0x28
    addAction(0x29); // FUN_004acf70
    addAction(0x2A); // FUN_004acf70
    addAction(0x28); // FUN_004acf70

    // Add action for state 0x25 again
    addAction(0x25); // FUN_004acff0

    // Add conditional transition "burstDone" with parameters (2, g_burstFireParam1, 1)
    addConditionalTransition("burstDone", 2, g_burstFireParam1, 1); // FUN_004acd80

    // Add transition from "postFireDelay" to nowhere
    addTransition("postFireDelay", 0xFFFFFFFF); // FUN_004adae0

    // Add conditional transition "burstDone" with parameters (2, g_burstFireParam2, 1)
    addConditionalTransition("burstDone", 2, g_burstFireParam2, 1); // FUN_004acd80

    // Add transition from "burstDone" to nowhere
    addTransition("burstDone", 0xFFFFFFFF); // FUN_004adae0

    // Add action for state 2
    addAction(2); // FUN_004acf70

    // Register the state machine with ID 0x211BC9C1, entry point at LAB_0076c1d0, and name "BurstFireSM"
    registerStateMachine(0x211BC9C1, &LAB_0076c1d0, "BurstFireSM"); // FUN_004adc90

    // Finalize state machine setup
    finalizeStateMachine(); // FUN_004ada40
}