// Xbox PDB: EARS_Apt_UIConnections_CollectCurrentGiverInfo
// FUNC_NAME: JobGiverManager::updateCurrentJobGiver
void __thiscall JobGiverManager::updateCurrentJobGiver() {
  int jobGiverData;
  int previousJobGiverData;
  int currentJobGiverContainer;
  int jobGiverActor;

  // Get the current job giver entry from the array at this+0x68 using index at this+0x74
  // Each entry is 8 bytes (pointer?)
  jobGiverData = *(int *)(*(int *)(this + 0x68) + *(int *)(this + 0x74) * 8);
  if (jobGiverData != 0) {
    // The container of the job giver is at jobGiverData - 0x48 (offset to embedder)
    currentJobGiverContainer = jobGiverData - 0x48;
    if (currentJobGiverContainer != 0) {
      // Copy position? (offsets 0x6c/0x70 relative to jobGiverData)
      *(int *)(this + 0x88) = *(int *)(jobGiverData + 0x6c);
      *(int *)(this + 0x8c) = *(int *)(jobGiverData + 0x70);
      // Get the actor pointer (prefer +0x1bc, fallback +0xb8)
      jobGiverActor = *(int *)(jobGiverData + 0x1bc);
      if (jobGiverActor == 0) {
        jobGiverActor = *(int *)(jobGiverData + 0xb8);
      }
      *(int *)(this + 0x90) = jobGiverActor;
      // Clear flag at +0xa1
      *((char *)this + 0xa1) = 0;
      // Display the job giver UI (likely a debug/script command)
      FUN_005a04a0("ShowCurrentJobGiver", 0, &DAT_00d861fc, 0);
      // Check if there was a previous job giver stored at this+0xa4
      int prevContainer = *(int *)(this + 0xa4);
      if (prevContainer == 0) {
        previousJobGiverData = 0;
      } else {
        previousJobGiverData = prevContainer - 0x48;
      }
      // If the current job giver container differs from the previous, hide the previous
      if (currentJobGiverContainer != previousJobGiverData) {
        FUN_00921430(currentJobGiverContainer);
      }
    }
  }
}