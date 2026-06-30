// FUNC_NAME: AudioManager::playSoundEffect
void AudioManager::playSoundEffect(void)
{
  int soundIndex;
  uint soundId;
  undefined4 local_a8 [4];
  undefined4 local_a4 [16];
  uint local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  
  // Check if sound ID is valid and sound is loaded
  if ((soundId < 0x100) && ((&g_soundLoadedFlags)[soundId] != 0)) {
    // Call virtual function at offset 0x28 (likely getSoundData or similar)
    (**(code **)(*DAT_012055a4 + 0x28))();
    
    // Call function to prepare sound playback
    FUN_005974f0(1, 0);
    
    soundIndex = (&g_soundLoadedFlags)[soundId];
    if (soundIndex == 0) {
      // Call virtual function at offset 4 (likely destructor or cleanup)
      (**(code **)(*DAT_01205590 + 4))();
    }
    
    // Set up sound parameters
    local_64 = local_64 & 0xfffffff9 | 1;  // Set bit 0, clear bits 1-3
    local_5c = 0;  // Volume
    local_58 = 0;  // Pan
    local_60 = *(undefined4 *)(soundIndex + 8);  // Sound data pointer
    
    // Call function to start playback (offset 0x40, likely playSound)
    (**(code **)(*DAT_012055a8 + 0x40))(local_a4);
    
    // Call function to finalize sound setup
    FUN_00597370(local_a8);
  }
  return;
}