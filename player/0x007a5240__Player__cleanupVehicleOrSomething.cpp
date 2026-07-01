// FUNC_NAME: Player::cleanupVehicleOrSomething
void __fastcall Player::cleanupVehicleOrSomething(int thisPtr)
{
  int *vehiclePtr;
  int hashResult;
  
  vehiclePtr = (int *)(thisPtr + 0x2190); // +0x2190: pointer to vehicle/entity
  if (*(int *)(thisPtr + 0x2190) != 0) {
    FUN_008ca010(*(int *)(thisPtr + 0x2190)); // likely release/delete vehicle
    if (*vehiclePtr != 0) {
      FUN_004daf90(vehiclePtr); // likely set pointer to null after deletion
      *vehiclePtr = 0;
    }
  }
  hashResult = FUN_00625050(0xc4bc3ce7,0); // hash lookup for some game state
  if (hashResult != 0) {
    FUN_007e34b0(); // likely handle special case (e.g., player in vehicle)
    return;
  }
  return;
}