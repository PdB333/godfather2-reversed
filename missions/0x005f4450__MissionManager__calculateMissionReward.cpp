// FUNC_NAME: MissionManager::calculateMissionReward
int __thiscall MissionManager::calculateMissionReward(int this, float missionTime)
{
  int missionIndex;
  int reward;
  float *pMissionTime;
  double dVar1;
  double local_10; // probably completion time
  double local_8;  // probably difficulty multiplier

  missionIndex = 0;
  pMissionTime = (float *)(this + 0x82b0); // +0x82b0: array of mission time limits (9 slots, stride 0x5c = 92 bytes)
  while (((int)*pMissionTime < 0 || (*pMissionTime != missionTime))) {
    missionIndex = missionIndex + 1;
    pMissionTime = pMissionTime + 0x5c;
    if (9 < missionIndex) {
      return -1;
    }
  }
  if (-1 < missionIndex) {
    // missionIndex is valid, get mission data at offset 0x8210 + missionIndex * 0x170
    reward = missionIndex * 0x170 + 0x8210 + this;
    FUN_00ab4db0(&DAT_00e2aea0); // likely some global state save/lock
    if ((((-1 < *(int *)(reward + 0xa0)) && // +0xa0: mission completion flag (>=0 means completed?)
         (*(int *)(*(int *)(reward + 0x9c) * 0x10 + 0x81c4 + this) != 0)) && // +0x81c4: pointer to array of mission objectives? Indexed by +0x9c
        (int dVar2 = FUN_005e9d10(), DAT_00e2b05c <= *(float *)(reward + 0x134))) && // +0x134: mission time limit? DAT_00e2b05c is a global threshold
        (dVar2 != 0)) { // FUN_005e9d10 likely a check (e.g., difficulty)
      FUN_00c9eac0(); // start random/stat calculation
      FUN_00c9cd00(0, &missionTime); // store missionTime as value 0
      FUN_00c9cd20(2, &local_10); // get value 2 (completion time?)
      FUN_00c9cd20(1, &local_8); // get value 1 (multiplier?)
      FUN_00c9eae0(); // finish calculation
      if ((missionTime == *(float *)(reward + 0x134)) && (_DAT_00e44568 < local_10)) {
        dVar1 = local_8 * DAT_00e44570; // DAT_00e44570 is a global multiplier
        FUN_00ab4e70(); // unlock/restore global state
        return (int)dVar1;
      }
    }
    FUN_00ab4e70(); // unlock/restore global state on failure
  }
  return -1;
}