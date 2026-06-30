// FUNC_NAME: AudioManager::play3DSound
undefined4 __thiscall AudioManager::play3DSound(int thisPtr, int soundId, float* outDurationMs)
{
  int i;
  int* slotPtr;
  int slotIndex;
  int sourceBase;
  int* soundSourceArray;
  int handle;
  int audioManager;
  float soundParams[6];
  
  // Search for a sound slot with matching ID and active state
  slotPtr = (int*)(thisPtr + 0x82ac);
  for (i = 0; i < 10; i++) {
    if (slotPtr[1] >= 0 && *slotPtr == soundId) {
      break;
    }
    slotPtr += 0x5c; // 0x5c = 92 bytes per slot
  }
  if (i >= 10) {
    return 0; // Slot not found
  }
  
  // Calculate source data offset: each source is 0x170 bytes, starting at 0x8210
  sourceBase = i * 0x170 + 0x8210 + thisPtr;
  
  // Check if the sound source handle is valid
  // soundSourceArray at offset 0x81c4, indexed by (sourceBase+0x9c)*0x10
  soundSourceArray = (int*)(thisPtr + 0x81c4);
  handle = *(int*)(sourceBase + 0x9c);
  if (soundSourceArray[handle * 0x10] == 0) {
    return 0; // Source not loaded
  }
  
  // Get the global audio manager singleton
  audioManager = FUN_005e9d10();
  
  // Set up 3D sound parameters (position, etc.)
  FUN_00c9cbe0(*(undefined4*)(thisPtr + 0x580), *(undefined4*)(audioManager + 0x10), 3, soundParams);
  
  // Lock critical section
  FUN_00ab4db0(&DAT_00e2aea0);
  
  // Read a parameter from the source (e.g., maximum distance)
  soundParams[0] = *(float*)(sourceBase + 0x134);
  if (soundParams[0] < DAT_00e2b05c) {
    FUN_00ab4e70(); // Unlock
    return 0; // Too close
  }
  
  // Perform audio processing
  FUN_00c9eac0(); // Begin audio update
  FUN_00c9cd40(3, soundParams); // Set 3D parameters
  FUN_00c9eae0(); // End audio update
  
  // Determine output duration based on distance
  if (soundParams[0] <= DAT_00e2b05c) {
    *outDurationMs = 0; // No duration
    FUN_00ab4e70(); // Unlock
    return 1;
  }
  *outDurationMs = 1000.0f; // 1 second duration
  FUN_00ab4e70(); // Unlock
  return 1;
}