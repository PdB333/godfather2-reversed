// FUNC_NAME: PlayerReputationTracker::getReputationMultiplier
float PlayerReputationTracker::getReputationMultiplier(void)
{
  int reputationValue;
  int maxReputation;
  float multiplier;
  float temp;

  multiplier = 0.0f;
  if ((DAT_01129904 != 0) && (reputationValue = FUN_008c74d0(0x637b907), reputationValue != 0)) {
    maxReputation = *(int *)(DAT_0112a558 + 0x44) + *(int *)(DAT_0112a558 + 0x40); // +0x40, +0x44: max reputation components
    temp = (float)maxReputation;
    if (maxReputation < 0) {
      temp = temp + (float)DAT_00e44578; // floating point adjustment constant
    }
    reputationValue = *(int *)(reputationValue + 0x118) + *(int *)(reputationValue + 0x10c); // +0x10c, +0x118: current reputation components
    multiplier = (float)reputationValue;
    if (reputationValue < 0) {
      multiplier = multiplier + (float)DAT_00e44578;
    }
    multiplier = multiplier * (DAT_00d5e288 / temp); // DAT_00d5e288: max multiplier cap (likely 1.0f or similar)
    if (multiplier <= DAT_00d5e288) {
      return multiplier;
    }
    multiplier = DAT_00d5e288;
  }
  return multiplier;
}