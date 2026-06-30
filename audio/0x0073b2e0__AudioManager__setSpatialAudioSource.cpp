// FUNC_NAME: AudioManager::setSpatialAudioSource
void __thiscall AudioManager::setSpatialAudioSource(int thisPtr, float* sourceData)
{
  int iVar1;
  int iVar2;

  // Check if sound type is ambient or disabled (0 or 0x48)
  if ((*(int *)(thisPtr + 0xa4) == 0) || (*(int *)(thisPtr + 0xa4) == 0x48)) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(thisPtr + 0xa0); // Pointer to transform/bone data
  }

  // Retrieve a preallocated sound event slot from the global singleton
  if (*(int *)(thisPtr + 0x5c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0043b870(DAT_01131064); // Returns pointer to a sound instance struct
  }

  // Fill the sound instance with source position/orientation
  *(undefined8 *)(iVar1 + 0x18) = *(undefined8 *)sourceData;            // Two floats (e.g., position.xy)
  *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(sourceData + 2);     // Third float (e.g., position.z)
  *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(iVar2 + 0xb4);       // Fourth float (e.g., orientation/velocity)
  *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(iVar2 + 0xb8);       // Fifth float
}