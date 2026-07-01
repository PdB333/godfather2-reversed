// Xbox PDB: EARS_Modules_RootVehicleSM_BuildStateTable
// FUNC_NAME: VehicleBrain::registerAllBehaviors
void VehicleBrain::registerAllBehaviors(void)
{
    int stateMachineId;
    
    stateMachineId = getVehicleStateMachineManager();
    registerVehicleState("RootVehicleST", stateMachineId);
    addGlobalTransition(&DAT_00d63420, 0xffffffff); // "any" transition?
    addBrainType("pickBrain", 4);
    addTransition("pickBrain", 0xffffffff);
    addBrainType(&DAT_00d64b74, 0xb); // likely "standardDriver"
    addBrainType("civilian", 0xc);
    addBrainType("chase", 0xd);
    addBrainType("policePatrol", 0xe);
    addBrainType("mobVenue", 0xf);
    addBrainType(&DAT_00d64b74, 4);
    addTransition(&DAT_00d64b74, 0xffffffff);
    setDefaultBrainType(10);
    addStateTable("VehicleIdleST", 1);
    addBrainType("pickBrain", 10);
    addTransition("civilian", 0xffffffff);
    setDefaultBrainType(10);
    addStateTable("civilianVehicleMainTable", 1);
    addBrainType("pickBrain", 10);
    addTransition("chase", 0xffffffff);
    setDefaultBrainType(10);
    addStateTable("vehicleChaseOffsetTable", 1);
    addBrainType("pickBrain", 10);
    addTransition("policePatrol", 0xffffffff);
    setDefaultBrainType(10);
    addStateTable("PoliceCarRootST", 1);
    addBrainType("pickBrain", 10);
    addTransition("mobVenue", 0xffffffff);
    setDefaultBrainType(10);
    addStateTable("MobCarRootST", 1);
    addBrainType("pickBrain", 10);
    registerRootStateMachine(0x70182f64, &LAB_00881ea0, "RootVehicleSM");
    finalizeInitialization();
    return;
}