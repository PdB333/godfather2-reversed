// Xbox PDB: EARS_Vehicles_AICarBehavior_RegisterAICarBehaviorMessages
// FUNC_NAME: VehicleMessageRegistration::registerVehicleMessages
void VehicleMessageRegistration::registerVehicleMessages(void)

{
  FUN_00408240(&DAT_0112dfcc,"iMsgSetVehicleSirenOn");
  FUN_00408240(&DAT_0112dfc4,"iMsgSetVehicleSirenOff");
  FUN_00408240(&DAT_0112dfb8,"iMsgVehicleIsReversing");
  return;
}