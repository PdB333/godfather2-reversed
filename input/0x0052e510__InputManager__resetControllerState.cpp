// FUNC_NAME: InputManager::resetControllerState
void InputManager::resetControllerState(void)

{
  undefined8 *puVar1;
  int iVar2;
  uint uVar3;
  
  // Clear 32 controller slots (0x20 = 32), each slot is 0x18 bytes (3 * 8 = 24 bytes)
  puVar1 = &DAT_01219390;  // Base of controller state array
  iVar2 = 0x20;  // 32 slots
  do {
    // Zero out each 0x18-byte slot (3 qwords = 24 bytes)
    *(undefined4 *)(puVar1 + -1) = 0;  // offset -8
    *(undefined4 *)((int)puVar1 + -4) = 0;  // offset -4
    *(undefined4 *)puVar1 = 0;  // offset 0
    *(undefined4 *)((int)puVar1 + 4) = 0;  // offset 4
    *(undefined4 *)(puVar1 + 1) = 0;  // offset 8
    *(undefined4 *)((int)puVar1 + 0xc) = 0;  // offset 12
    puVar1 = puVar1 + 3;  // Advance 3 qwords (24 bytes)
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  
  // Clear additional state variables at DAT_01219828..DAT_01219859
  DAT_01219858 = 0;  // +0x4C8? (relative to base)
  DAT_01219828 = 0;  // +0x498
  DAT_0121982c = 0;  // +0x49C
  DAT_01219830 = 0;  // +0x4A0
  DAT_01219834 = 0;  // +0x4A4
  _DAT_01219838 = 0; // +0x4A8
  _DAT_0121983c = 0; // +0x4AC
  _DAT_01219840 = 0; // +0x4B0
  _DAT_01219844 = 0; // +0x4B4
  _DAT_01219848 = 0; // +0x4B8
  _DAT_0121984c = 0; // +0x4BC
  _DAT_01219850 = 0; // +0x4C0
  _DAT_01219854 = 0; // +0x4C4
  DAT_01219859 = 0;  // +0x4C9 (byte)
  
  // Initialize per-slot data: clear some arrays and copy default values
  iVar2 = 0;
  uVar3 = 0;
  do {
    (&DAT_01219708)[iVar2] = 0;  // Clear array at +0x378 (32 entries)
    (&DAT_01219788)[iVar2] = *(undefined4 *)(&DAT_0121939c + uVar3);  // Copy default from +0x00C (first slot's data)
    (&DAT_01219808)[iVar2] = 0;  // Clear array at +0x478 (32 entries)
    uVar3 = uVar3 + 0x18;  // 0x18 = 24 bytes per slot
    iVar2 = iVar2 + 1;
  } while (uVar3 < 0x300);  // 0x300 = 768 = 32 * 24, so loop 32 times
  
  // If there's an active device, release it
  if (DAT_01205524 != 0) {
    FUN_006065a0(DAT_01205524, 0);  // Likely releaseDevice or closeDevice
  }
  DAT_01205524 = 0;  // Clear device handle
  return;
}