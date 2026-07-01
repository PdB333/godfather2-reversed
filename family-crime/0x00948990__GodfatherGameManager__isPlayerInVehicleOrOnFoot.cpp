// FUNC_NAME: GodfatherGameManager::isPlayerInVehicleOrOnFoot
undefined4 __fastcall GodfatherGameManager::isPlayerInVehicleOrOnFoot(int *thisPtr)

{
  // Check if player is in a vehicle (param_1[8] == 1) or on foot (param_1[8] == 2)
  // +0x00: player state flags? (4 ints for position/state)
  // +0x10: vehicle state? (param_1[4])
  // +0x14: vehicle pointer? (param_1[5])
  // +0x20: player mode (param_1[8]) - 1=vehicle, 2=on foot
  
  if (((thisPtr[8] != 1) ||
      // If in vehicle mode, check if vehicle exists (position non-zero)
      ((((*thisPtr == 0 && (thisPtr[1] == 0)) && (thisPtr[2] == 0)) && (thisPtr[3] == 0)))) &&
     // If not in vehicle mode, check if on foot mode with valid state
     ((thisPtr[8] != 2 || (thisPtr[5] == 0)))) {
    return 0;  // Not in valid vehicle or on foot state
  }
  return 1;  // Player is either in a vehicle or on foot
}