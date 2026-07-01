// FUNC_NAME: GodfatherGameManager::resetGameState
void __fastcall GodfatherGameManager::resetGameState(GodfatherGameManager *this)

{
  uint *puVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  FUN_00957eb0(); // likely some engine reset or cleanup
  if (*(int *)(this + 100) != 0) { // +0x64: some state flag
    iVar2 = 0;
    do {
      puVar1 = (uint *)(iVar2 + 0x18 + DAT_0112989c); // +0x18: offset into some array
      if (puVar1 != (uint *)0x0) {
        *puVar1 = *puVar1 & 0xfffffffb; // clear bit 2 (0x4)
      }
      iVar2 = iVar2 + 0x24; // stride 0x24 (36 bytes) per element
    } while (iVar2 < 0xfc); // 0xfc / 0x24 = 7 iterations
    local_c = DAT_01130430; // some global data
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0); // likely a memset or reset
    FUN_00956ab0(0); // reset some subsystem
    if (*(int *)(DAT_01130020 + 0x78) < 1) { // +0x78: some counter
      FUN_0097b630(1,1); // enable something
      FUN_00976370(0); // disable something
      FUN_00956ad0(); // finalize reset
    }
  }
  *(undefined1 *)(this + 0x12a) = 0; // +0x12a: byte flag
  *(undefined1 *)(this + 299) = 0; // +0x12b: byte flag
  *(undefined4 *)(this + 100) = 0; // +0x64: state flag
  *(undefined4 *)(this + 0x60) = 0; // +0x60: some pointer/flag
  *(undefined4 *)(this + 0x11c) = 0; // +0x11c: some field
  *(undefined4 *)(this + 0x134) = 0; // +0x134: some field
  *(undefined4 *)(this + 0x130) = 0xffffffff; // +0x130: set to -1
  return;
}