// Xbox PDB: EARS_Modules_VehicleEntrySM_BuildStateMachine
// FUNC_NAME: VehicleEntryStateMachine::buildStateTable
void VehicleEntryStateMachine::buildStateTable(void)
{
    // Get state machine system singleton
    int stateMachineHandle = FUN_009c8f80();
    FUN_004ad9d0("vehicleEntryStateTable", stateMachineHandle);
    
    // Initialize state data
    FUN_004adae0(&DAT_00d63420, 0);
    FUN_004acf70(10);
    
    // State: stopAtVehicle
    FUN_004acc70("stopAtVehicle", 4);
    FUN_004adae0("stopAtVehicle", 1);
    FUN_004acf70(0x10);
    FUN_004acf70(0xb);
    
    // State: Terminate
    FUN_004acc70("Terminate", 0xe);
    
    // State: teleportEntry
    FUN_004acc70("teleportEntry", 10);
    
    // State: waitForIdleDoor
    FUN_004acc70("waitForIdleDoor", 4);
    FUN_004adae0("waitForIdleDoor", 2);
    FUN_004acf70(0x11);
    FUN_004acf70(8);
    FUN_004acff0(8);
    
    // State: Terminate
    FUN_004acc70("Terminate", 0xe);
    
    // State: trackToVehicle
    FUN_004acc70("trackToVehicle", 0xc);
    FUN_004adae0("trackToVehicle", 3);
    FUN_004acf70(0xc);
    FUN_004acf70(0x12);
    FUN_004acf70(0x14);
    FUN_004acff0(0x14);
    
    // State: Terminate
    FUN_004acc70("Terminate", 0xe);
    
    // State: enterVehicle
    FUN_004acc70("enterVehicle", 0xd);
    FUN_004adae0("enterVehicle", 4);
    FUN_004acf70(0xd);
    FUN_004acf70(0x15);
    FUN_004acff0(0x15);
    
    // State: Terminate
    FUN_004acc70("Terminate", 0xe);
    
    // State: enteredVehicle
    FUN_004acc70("enteredVehicle", 7);
    FUN_004adae0("enteredVehicle", 5);
    
    // State: Terminate
    FUN_004acc70("Terminate", 0xe);
    FUN_004acc70("Terminate", 7);
    
    // Finalize states
    FUN_004ad070(0x13);
    FUN_004ad070(0xe);
    FUN_004ad070(0xf);
    FUN_004adae0("teleportEntry", 6);
    FUN_004acf70(0xc);
    FUN_004acf70(0xe);
    
    // State: Terminate
    FUN_004acc70("Terminate", 0xe);
    FUN_004acc70("Terminate", 4);
    FUN_004adae0("Terminate", 7);
    FUN_004acf70(2);
    
    // Register the state machine
    FUN_004adc90(0xfa2c42b8, FUN_008837a0, "VehicleEntrySM");
    FUN_004ada40();
    
    return;
}