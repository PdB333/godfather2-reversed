// FUNC_NAME: AudioManager::initAudioHandle
void __thiscall FUN_008904e0(void)

{
  // Allocate a new audio handle structure (size 0x20 bytes)
  DAT_0112e2dc = FUN_009c8e50(0x20);
  if (DAT_0112e2dc != 0) {
    // Initialize the audio handle structure
    // +0x00: (pointer to vtable or interface) intentionally left uninitialized
    // +0x04: pointer to sound data table at 0x00ef4398
    *(undefined4 **)(DAT_0112e2dc + 4) = &DAT_00ef4398;
    // +0x08: flags/state set to 1 (active)
    *(undefined4 *)(DAT_0112e2dc + 8) = 1;
    // +0x0C: unknown field set to 0
    *(undefined4 *)(DAT_0112e2dc + 0xc) = 0;
    // +0x10: some sample or rate parameter from global _DAT_00d5780c
    *(undefined4 *)(DAT_0112e2dc + 0x10) = _DAT_00d5780c;
    // +0x14: another parameter from DAT_00d5eee4
    *(undefined4 *)(DAT_0112e2dc + 0x14) = DAT_00d5eee4;
    // +0x18: unknown field set to 0
    *(undefined4 *)(DAT_0112e2dc + 0x18) = 0;
    return;
  }
  // Allocation failed, clear the global handle pointer
  DAT_0112e2dc = 0;
  return;
}