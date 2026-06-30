// FUNC_NAME: AssetDevManager::processAssetUpdateQueue
undefined4 AssetDevManager::processAssetUpdateQueue(undefined4 param_1, undefined4 param_2, undefined4 param_3)

{
  char cVar1;
  int iVar2;
  uint local_10 [3];
  code *local_4;
  
  iVar2 = DAT_01129f8c; // Pointer to head of asset update queue
  if (DAT_01129f8c != DAT_01129f90) { // Check if queue is non-empty (start != end)
    do {
      FUN_004d3bc0(param_1); // Probably AssetDevManager::processPendingAsset
      cVar1 = FUN_00699840(local_10, param_2, param_3); // Extract next asset update from queue
      if (local_10[0] != 0) {
        (*local_4)(local_10[0]); // Execute callback/apply function for this asset update
      }
      if (cVar1 != '\0') {
        return 1; // Early return if processing complete or error
      }
      iVar2 = iVar2 + 4; // Advance to next queue element
    } while (iVar2 != DAT_01129f90); // Continue until end of queue
  }
  return 0; // All updates processed
}