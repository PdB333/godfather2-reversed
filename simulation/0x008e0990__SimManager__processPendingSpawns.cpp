// FUNC_NAME: SimManager::processPendingSpawns
void __thiscall SimManager::processPendingSpawns(int thisPtr, undefined4 param_2)
{
  char bIsPending;
  int iSpawnedObj;
  
  // Initialize the spawn queue or pending list
  FUN_008dab90(param_2);
  
  // Set a flag or state (0x88206c94 appears to be a magic constant for "spawn pending")
  FUN_0043aff0(param_2, 0x88206c94);
  
  bIsPending = FUN_0043b120();  // Check if there are pending spawns
  while (bIsPending == '\0') {
    // Process the next pending spawn
    FUN_0043b210();
    
    iSpawnedObj = FUN_0043ab70();  // Try to spawn the object
    if (iSpawnedObj == 0) {
      // Spawn succeeded, get the object and store it
      iSpawnedObj = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x210) = *(undefined4 *)(iSpawnedObj + 8);  // +0x210: currentSpawnedObject
    }
    
    // Advance to next pending spawn
    FUN_0043b1a0();
    
    bIsPending = FUN_0043b120();  // Check for more pending spawns
  }
  return;
}