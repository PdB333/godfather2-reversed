// FUNC_NAME: GodfatherGameManager::resetGameState
void __fastcall GodfatherGameManager::resetGameState(int this)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // Clear game state flags at +0x84
  *(undefined4 *)(this + 0x84) = 0;
  
  // Reset audio/music systems
  FUN_00455be0(0);
  FUN_004e0630(0);
  
  // Clear bit 2 (0x4) of flags at global+0x10
  *(uint *)(DAT_011298d4 + 0x10) = *(uint *)(DAT_011298d4 + 0x10) & 0xfffffffb;
  
  // Reset UI state
  FUN_0088d6b0();
  
  // Clear bit 4 (0x10) of flags at global+0x6c
  *(uint *)(DAT_01223394 + 0x6c) = *(uint *)(DAT_01223394 + 0x6c) & 0xffffffef;
  
  // Reset player state
  FUN_0093a2f0();
  
  // Set timer to 8 seconds
  FUN_0040eaf0(8);
  
  // If bit 0 of +0x90 is set, play a sound
  if ((*(byte *)(this + 0x90) & 1) != 0) {
    FUN_0040c2c0(DAT_00d75024, *(undefined4 *)(this + 0xa8), 1, 0x10);
  }
  
  // Enable something (likely input)
  FUN_0068c590(1);
  
  // Reset two vector3 values to zero
  local_c = *(undefined4 *)(this + 0x58);
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0);
  
  // Reset global vector
  FUN_004086d0(&DAT_0112ddd8);
  local_c = DAT_0112dde8;
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0);
  
  return;
}