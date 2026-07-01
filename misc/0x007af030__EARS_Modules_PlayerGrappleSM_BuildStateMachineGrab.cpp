// Xbox PDB: EARS_Modules_PlayerGrappleSM_BuildStateMachineGrab
// FUNC_NAME: PlayerGrappleSM::initiateGrappleStates
// Address: 0x007af030
// This function initializes animation states and transitions for grapple/combat interactions.

void __thiscall PlayerGrappleSM::initiateGrappleStates(void)
{
    // Set animation parameters for grapple (likely index, value, flag)
    FUN_004ad0f0(0x20, 0x3f, 1);  // e.g., setAnimParam(32, 63, 1)
    FUN_004ad0f0(0x22, 2, 1);    // setAnimParam(34, 2, 1)
    FUN_004ad0f0(0x12, 0, 1);    // setAnimParam(18, 0, 1)

    // Set state flags for various grapple states (single int state IDs)
    FUN_004acf70(0x46); // enableState(70)
    FUN_004acf70(0x43); // enableState(67)
    FUN_004acf70(0x6e); // enableState(110)

    // Register named states with their IDs
    FUN_004acc70("GrabEnd", 0x13);                // registerState("GrabEnd", 19)
    FUN_004acc70("PairedFinisher", 0x51);         // registerState("PairedFinisher", 81)

    // Add transitions from "PairedFinisher" (ID 0x50) to other states with parameters
    FUN_004acd20("PairedFinisher", 0x50, 10, 1);   // addTransition("PairedFinisher", 80, 10, 1)
    FUN_004acd20("PairedFinisher", 0x50, 0x1c, 1); // addTransition("PairedFinisher", 80, 28, 1)
    FUN_004acd20("PairedFinisher", 0x50, 8, 1);    // addTransition("PairedFinisher", 80, 8, 1)
    FUN_004acd20("PairedFinisher", 0x50, 0x1a, 1); // addTransition("PairedFinisher", 80, 26, 1)

    // Register execution states
    FUN_004acc70("Execution", 0x4e);              // registerState("Execution", 78)
    FUN_004acc70("Execution", 0x17);              // registerState("Execution", 23)

    // Add transitions from "Execution" (ID 0x15) to other states
    FUN_004acd20("Execution", 0x15, 1, 1);        // addTransition("Execution", 21, 1, 1)
    FUN_004acd20("Execution", 0x15, 2, 1);        // addTransition("Execution", 21, 2, 1)

    // Register another execution state
    FUN_004acc70("Execution", 0x16);              // registerState("Execution", 22)

    // Register grab-related states
    FUN_004acc70("GrabConcealWeaponStart", 0x18); // registerState("GrabConcealWeaponStart", 24)
    FUN_004acc70("GrabFront", 0x1a);              // registerState("GrabFront", 26)
    FUN_004acc70("GrabBehind", 0x1b);             // registerState("GrabBehind", 27)
    FUN_004acc70("GrabEndPaired", 4);             // registerState("GrabEndPaired", 4)

    return;
}