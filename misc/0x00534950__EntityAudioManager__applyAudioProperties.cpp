// FUNC_NAME: EntityAudioManager::applyAudioProperties
void __fastcall EntityAudioManager::applyAudioProperties(int thisPtr)
{
  int audioHandle;
  undefined4 *audioDataPtr;

  // Store this pointer globally (likely for debug/access)
  DAT_012058e8 = thisPtr;

  // Release previous audio sources (assuming 0x10 and 0x14 are audio source pointers)
  FUN_0060a460(*(undefined4 *)(thisPtr + 0x10));
  FUN_0060a460(*(undefined4 *)(thisPtr + 0x14));

  // Apply audio properties from 0x30-byte arrays indexed by byte at +0xB0
  // +0xB0 seems to be an index into an array of audio property definitions (0x30 each)
  // The array starts at +0x23C (offset into the class)
  audioHandle = *(int *)((uint)*(byte *)(thisPtr + 0xB0) * 0x30 + 0x23C + thisPtr);
  if (audioHandle != 0) {
    // Set audio property with position data at +0xD0
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x10), audioHandle, thisPtr + 0xD0);
  }

  // Different offset pattern: uses (index + 0xC) * 0x30
  audioHandle = *(int *)((*(byte *)(thisPtr + 0xB0) + 0xC) * 0x30 + thisPtr);
  if (audioHandle != 0) {
    FUN_0060b020(*(undefined4 *)(thisPtr + 0x10), audioHandle, thisPtr + 0xE0);
  }

  // More property applications with different offsets
  audioHandle = *(int *)((uint)*(byte *)(thisPtr + 0xB0) * 0x30 + 0x260 + thisPtr);
  if (audioHandle != 0) {
    FUN_0060b020(*(undefined4 *)(thisPtr + 0x10), audioHandle, thisPtr + 0x160);
  }

  audioHandle = *(int *)((uint)*(byte *)(thisPtr + 0xB0) * 0x30 + 0x264 + thisPtr);
  if (audioHandle != 0) {
    // Different function with parameter 3 (probably different application mode)
    FUN_0060aea0(*(undefined4 *)(thisPtr + 0x10), audioHandle, thisPtr + 0x160, 3);
  }

  // Property at offset 600 (0x258)
  audioHandle = *(int *)((uint)*(byte *)(thisPtr + 0xB0) * 0x30 + 600 + thisPtr);
  if (audioHandle != 0) {
    // Use position from +0xC4 (vector3)
    undefined4 local_20[4];
    local_20[0] = *(undefined4 *)(thisPtr + 0xC4);
    local_20[1] = 0;
    local_20[2] = 0;
    local_20[3] = 0;
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x10), audioHandle, &local_20);
  }

  // More properties with different positions
  audioHandle = *(int *)((uint)*(byte *)(thisPtr + 0xB0) * 0x30 + 0x254 + thisPtr);
  if (audioHandle != 0) {
    FUN_0060b020(*(undefined4 *)(thisPtr + 0x10), audioHandle, thisPtr + 0x120);
  }

  // Conditional audio data pointer based on byte at +0xC8 (0x200 in decimal)
  audioHandle = *(int *)((uint)*(byte *)(thisPtr + 0xB0) * 0x30 + 0x268 + thisPtr);
  if (audioHandle != 0) {
    audioDataPtr = &DAT_011280d0; // Default audio data
    if (*(char *)(thisPtr + 200) == '\0') {
      audioDataPtr = &DAT_00e2e770; // Alternative audio data
    }
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x10), audioHandle, audioDataPtr);
  }

  // Another position-based property
  audioHandle = *(int *)((uint)*(byte *)(thisPtr + 0xB0) * 0x30 + 0x25C + thisPtr);
  if (audioHandle != 0) {
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x10), audioHandle, thisPtr + 0x1B0);
  }

  // Second audio source with different index (byte at +0xB1) and 0x3C-byte stride
  audioHandle = *(int *)(thisPtr + 0x300 + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C);
  if (audioHandle != 0) {
    audioDataPtr = &DAT_01163810;
    if (DAT_01163840 == '\0') {
      audioDataPtr = &DAT_00e2e760;
    }
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x14), audioHandle, audioDataPtr);
  }

  audioHandle = *(int *)(thisPtr + 0x304 + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C);
  if (audioHandle != 0) {
    audioDataPtr = &DAT_011637d0;
    if (DAT_01163840 == '\0') {
      audioDataPtr = &DAT_00e2e720;
    }
    FUN_0060b020(*(undefined4 *)(thisPtr + 0x14), audioHandle, audioDataPtr);
  }

  // Check various other properties and clear/stop if needed
  if (*(int *)(thisPtr + 0x2CC + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C) != 0) {
    FUN_006063b0(); // Likely stopAudio or similar
  }
  if (*(int *)(thisPtr + (*(byte *)(thisPtr + 0xB1) + 0xC) * 0x3C) != 0) {
    FUN_006063b0();
  }
  if (*(int *)(thisPtr + 0x2DC + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C) != 0) {
    FUN_006063b0();
  }
  if (*(int *)(thisPtr + 0x2E0 + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C) != 0) {
    FUN_006063b0();
  }

  // Apply remaining properties for second audio source
  audioHandle = *(int *)(thisPtr + 0x2EC + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C);
  if (audioHandle != 0) {
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x14), audioHandle, thisPtr + 0x1A0);
  }

  audioHandle = *(int *)(thisPtr + 0x2F0 + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C);
  if (audioHandle != 0) {
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x14), audioHandle, &DAT_011f6680);
  }

  if (*(int *)(thisPtr + 0x2F4 + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C) != 0) {
    FUN_006063b0();
  }

  audioHandle = *(int *)(thisPtr + 0x2F8 + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C);
  if (audioHandle != 0) {
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x14), audioHandle, thisPtr + 0x1C0);
  }

  audioHandle = *(int *)(thisPtr + 0x2FC + (uint)*(byte *)(thisPtr + 0xB1) * 0x3C);
  if (audioHandle != 0) {
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x14), audioHandle, thisPtr + 0x1D0);
  }
}