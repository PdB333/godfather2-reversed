// FUNC_NAME: AudioDataManager::createStreamInstance
int AudioDataManager::createStreamInstance(void)

{
  undefined4 streamHandle;
  int instanceIndex;
  int *pResult;
  int local_4;
  
  local_4 = 0;
  *unaff_ESI = 0;
  streamHandle = FUN_00672e60(); // GetOrCreateStreamHandle() - likely from BNKStreamManager
  if (*unaff_ESI == 0) {
    *unaff_ESI = 0;
    instanceIndex = FUN_00673070(); // AllocateStreamInstanceSlot() - returns index or -1
    if (instanceIndex != 0) {
      FUN_00672630(&local_4); // InitializeStreamInstance at local_4
      *(undefined4 *)(local_4 + 0x28) = streamHandle; // +0x28: stream handle
      *(undefined4 *)(local_4 + 0x2c) = 0;             // +0x2c: volume (default 0)
      *(undefined4 *)(local_4 + 0x30) = 0;             // +0x30: pitch (default 0)
      return local_4;
    }
    *unaff_ESI = 0x2718; // Error code 10008 (no free slot)
  }
  return 0;
}