// Xbox PDB: EARS_Modules_PlayerVehicleSM_BuildStateMachine
// FUNC_NAME: PlayerVehicleSM::Initialize
// Function address: 0x007d49b0
// Purpose: Constructs the Player Vehicle State Machine (PlayerVehicleSM) by defining states, transitions, and state tables.
// Uses EA state machine framework (similar to FSMBuilder).
// Assumes static methods: GetStateMachineContext(), AddStateTable(), AddTransition(), AddState(), SetInitialState(), 
// AddStateGroup(), RegisterStateMachine(), Finalize().

void PlayerVehicleSM::Initialize(void)
{
    uint contextId;

    // Retrieve the context ID for the state machine (likely a module or system handle)
    contextId = GetStateMachineContext();

    // Register the top-level player vehicle state table
    AddStateTable("playerVehicleStateTable", contextId);

    // Define initial state "start" with ID 0xFFFFFFFF (likely a placeholder or "any")
    AddTransition("start", 0xffffffff);

    // Add a state table "playerVehicleStateTable" with priority 3? (or group 3?)
    AddStateTable(&DAT_00d63420, 3); // DAT_00d63420 appears to be a string reference, possibly "playerVehicleStateTable" again
    AddTransition(&DAT_00d63420, 0xffffffff);

    // Add state "holsterWeapon" with ID 0x14 (20)
    AddState("holsterWeapon", 0x14);
    // Add state "enterVehicle" with ID 4
    AddState("enterVehicle", 4);
    // Set transition from "holsterWeapon" to nowhere? (ID -1)
    AddTransition("holsterWeapon", 0xffffffff);

    // Define a sub-state table for concealing items
    SetInitialState("playerConcealItemStateTable", 1);
    AddState("enterVehicle", 1); // transition to enterVehicle in that sub-table?
    AddTransition("enterVehicle", 0xffffffff);

    // Define vehicle entry state table
    SetInitialState("vehicleEntryStateTable", 1);
    AddStateGroup(0x32); // group ID 50
    AddState("vehicleExploded", 0x16); // ID 22
    AddState("Terminate", 0x15); // ID 21
    AddState("updateVehicle", 1);
    AddState(0x33); // ID 51
    AddTransition("updateVehicle", 0xffffffff);
    AddState(0x31); // ID 49
    AddState(0x37); // ID 55
    AddState("Terminate", 0x15);
    AddState("exitVehicleButtonPressed", 0x13); // ID 19
    AddTransition("exitVehicleButtonPressed", 0xffffffff);

    // Another group for vehicle exit / forced exit
    AddStateGroup(0x39); // group ID 57
    AddState("teleportOutOfVehicle", 0x19); // ID 25
    AddState("exitVehicle", 0x18); // ID 24
    AddState("teleportOutOfVehicle", 0x17); // ID 23
    AddTransition("teleportOutOfVehicle", 0xffffffff);

    // Another group for vehicle explosion handling
    AddStateGroup(0x3a); // group ID 58
    AddState("vehicleExploded", 0x16);
    AddState("Terminate", 0x15);
    AddTransition("exitVehicle", 0xffffffff);

    // Define vehicle exit state table
    SetInitialState("vehicleExitStateTable", 1);
    AddStateGroup(0x34); // group ID 52
    AddState("vehicleExploded", 0x16);
    AddState("Terminate", 1);
    AddState(0x35); // ID 53
    AddState(0x36); // ID 54
    AddTransition("vehicleExploded", 0xffffffff);

    // Final group with various termination states
    AddStateGroup(0x38); // group ID 56
    AddState("Terminate", 4);
    AddTransition("Terminate", 0xffffffff);

    AddStateGroup(2);
    RegisterStateMachine(0xe76c9833, &LAB_007d4970, "PlayerVehicleSM"); // Register the complete machine with handler at 0x007d4970
    Finalize();
    return;
}