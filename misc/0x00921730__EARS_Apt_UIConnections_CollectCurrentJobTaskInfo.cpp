// Xbox PDB: EARS_Apt_UIConnections_CollectCurrentJobTaskInfo
// FUNC_NAME: JobManager::updateCurrentJobTask
int __fastcall JobManager::updateCurrentJobTask(int thisPtr)
{
  int jobDataPtr;
  int jobIndex;
  byte isPlayerJob;
  int currentJobPtr;
  int prevJobPtr;

  // Get job data pointer from array at +0x5c, indexed by current job index at +0x74
  jobDataPtr = *(int *)(*(int *)(thisPtr + 0x5c) + *(int *)(thisPtr + 0x74) * 8);
  jobIndex = *(int *)(thisPtr + 0x5c) + *(int *)(thisPtr + 0x74) * 8;

  if ((jobDataPtr != 0) && (currentJobPtr = jobDataPtr + -0x48, currentJobPtr != 0)) {
    // Copy job position/state from job data (+0x6c, +0x70) to this object (+0x88, +0x8c)
    *(undefined4 *)(thisPtr + 0x88) = *(undefined4 *)(jobDataPtr + 0x6c);
    *(undefined4 *)(thisPtr + 0x8c) = *(undefined4 *)(jobDataPtr + 0x70);

    // Get job target entity pointer: prefer +0x1bc, fallback to +0xb8
    jobIndex = *(int *)(jobDataPtr + 0x1bc);
    if (jobIndex == 0) {
      jobIndex = *(int *)(jobDataPtr + 0xb8);
    }
    *(int *)(thisPtr + 0x90) = jobIndex;

    // Check if job type (+0xc) is 2 (player job)
    isPlayerJob = 0;
    if (*(int *)(jobDataPtr + 0xc) == 2) {
      jobIndex = FUN_00950b00(); // GetPlayerManager or similar
      if (jobIndex != 0) {
        // Check if player is local (bit 1 of +0x84) and invert
        isPlayerJob = ~(byte)(*(uint *)(jobIndex + 0x84) >> 1) & 1;
      }
    }
    *(byte *)(thisPtr + 0xa1) = isPlayerJob;

    // Call debug/log function with "ShowCurrentJobTask"
    FUN_005a04a0("ShowCurrentJobTask", 0, &DAT_00d861fc, 0);

    // Check if previous job pointer (+0xa4) differs from current
    if (*(int *)(thisPtr + 0xa4) == 0) {
      prevJobPtr = 0;
    } else {
      prevJobPtr = *(int *)(thisPtr + 0xa4) + -0x48;
    }
    if (currentJobPtr != prevJobPtr) {
      jobIndex = FUN_00921430(currentJobPtr); // StartJob or similar
    }
  }
  return jobIndex;
}