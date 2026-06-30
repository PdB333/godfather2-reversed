// FUNC_NAME: AudioDataManager::releaseAudioData
void AudioDataManager::releaseAudioData(void)
{
  int thisPtr = in_EAX;
  int iVar1;
  
  // Check if audio data is not currently loaded (flag at +0x28)
  if (*(char *)(thisPtr + 0x28) == '\0') {
    // If there's a sound handle at +0x1c, release it via the audio system
    if (*(int *)(thisPtr + 0x1c) != 0) {
      // Call audio system's release function (vtable at DAT_01205868, offset +4)
      (**(code **)(*DAT_01205868 + 4))(*(int *)(thisPtr + 0x1c), *(undefined4 *)(thisPtr + 0x20));
      *(undefined4 *)(thisPtr + 0x1c) = 0;
    }
    
    // Remove from the active audio data list (critical section protected)
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_012224f8);
    iVar1 = 0;
    if (0 < DAT_01205854) {  // DAT_01205854 = count of active audio data entries
      while ((&DAT_011e28f0)[iVar1] != thisPtr) {  // DAT_011e28f0 = array of audio data pointers
        iVar1 = iVar1 + 1;
        if (DAT_01205854 <= iVar1) {
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_012224f8);
          return;
        }
      }
      // Found the entry, remove it by swapping with last element
      DAT_01205854 = DAT_01205854 + -1;
      if (0 < DAT_01205854) {
        (&DAT_011e28f0)[iVar1] = (&DAT_011e28f0)[DAT_01205854];
      }
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_012224f8);
  }
  else {
    // Audio data is still loading (flag at +0x28 is non-zero)
    // Cancel the async load operation
    FUN_0060bfa0();  // Likely cancelAsyncLoad()
    iVar1 = *(int *)(thisPtr + 0x2c);  // +0x2c = pending load handle
    if (iVar1 != 0) {
      if (DAT_01205868 != (int *)0x0) {
        (**(code **)(*DAT_01205868 + 4))(iVar1, 0);  // Release pending load
      }
      if (thisPtr != iVar1) {
        *(undefined4 *)(thisPtr + 0x2c) = 0;
        return;
      }
    }
  }
  return;
}