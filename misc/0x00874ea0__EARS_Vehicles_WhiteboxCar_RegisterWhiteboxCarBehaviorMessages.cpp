// Xbox PDB: EARS_Vehicles_WhiteboxCar_RegisterWhiteboxCarBehaviorMessages
// FUNC_NAME: MessageRegistry::registerAllMessages
void MessageRegistry::registerAllMessages(void)
{
    // Register all game messages with string identifiers
    FUN_00408240(&DAT_0112e104, "iMsgSetPoliceLightOn");
    FUN_00408240(&DAT_0112e0f4, "iMsgSetPoliceLightOff");
    FUN_00408240(&DAT_0112e054, "iMsgSetEnablePoliceVehicleSpawning");
    FUN_00408240(&DAT_0112e04c, "iMsgSetDisablePoliceVehicleSpawning");
    FUN_00408240(&DAT_0112e124, "iMsgDespawnAllSpawnedPoliceVehicles");
    FUN_00408240(&DAT_0112e028, "iMsgEnteringVehicleEvent");
    FUN_00408240(&DAT_0112e12c, "iMsgSentientEnterVehicle");
    FUN_00408240(&DAT_0112e13c, "iMsgSentientExitVehicle");
    FUN_00408240(&DAT_0112e05c, "iMsgSentientExitedVehicle");
    FUN_00408240(&DAT_0112e030, "iMsgPlayerAsDriverEnterVehicle");
    FUN_00408240(&DAT_0112e11c, "iMsgPlayerAsPassengerEnterVehicle");
    FUN_00408240(&DAT_0112e018, "iMsgPlayerExitVehicle");
    FUN_00408240(&DAT_0112e038, "iMsgSetFamilyToCorleone");
    FUN_00408240(&DAT_0112e064, "iMsgInternalWarnAIPeriodicBroadcast");
    FUN_00408240(&DAT_0112e040, "iMsgPlayerVehicleExplode");
    FUN_00408240(&DAT_0112e10c, "iMsgOccupantsSpawned");
    FUN_00408240(&DAT_0112e06c, "iMsgOccupantsDeSpawned");
    FUN_00408240(&DAT_0112e134, "iMsgOccupantsToldToExit");
    return;
}