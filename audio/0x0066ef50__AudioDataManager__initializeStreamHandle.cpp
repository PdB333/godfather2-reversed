// FUNC_NAME: AudioDataManager::initializeStreamHandle
void AudioDataManager::initializeStreamHandle(void) {
  int allocationResult;
  undefined4 streamHandle;
  undefined local_12[12]; // +0x00: struct for initialization (3 dwords)
  
  allocationResult = FUN_009c8e50(0x48); // Allocate 72 bytes for stream handle
  if (allocationResult != 0) {
    local_12[0] = 0;
    local_12[4] = 0;  // offset 0x04
    local_12[8] = 0;  // offset 0x08
    streamHandle = FUN_004b4d10(local_12); // Initialize with zeroed struct
    *(undefined4 *)(this + 0xa1c) = streamHandle; // Store handle at offset 0xa1c
    return;
  }
  *(undefined4 *)(this + 0xa1c) = 0; // Allocation failed, store null
  return;
}