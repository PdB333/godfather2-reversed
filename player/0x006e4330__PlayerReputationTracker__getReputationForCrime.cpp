// FUNC_NAME: PlayerReputationTracker::getReputationForCrime
void PlayerReputationTracker::getReputationForCrime(float *outReputation)

{
  undefined4 *vtablePtr;
  int playerPtr;
  char result;
  float10 reputationValue;
  undefined4 retaddr;
  
  playerPtr = (int)this;
  vtablePtr = (undefined4 *)((int)this + 0x100);
  this = (float *)0x0;
  result = (**(code **)(*(int *)*vtablePtr + 0x10))(0x383225a1, &this); // QueryInterface or similar
  if ((result != '\0') && (playerPtr != 0)) {
    reputationValue = (float10)FUN_006e3f90(playerPtr, retaddr, 
                                            DAT_00e44564 - *(float *)(playerPtr + 0x2890), // Crime severity offset
                                            _DAT_00d5fa88, DAT_00d5ccf8);
    *outReputation = (float)reputationValue;
    return;
  }
  *outReputation = 0.0;
  return;
}