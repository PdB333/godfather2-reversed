// FUNC_NAME: GodfatherGameManager::initializeGameSettings
void GodfatherGameManager::initializeGameSettings(void)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint in_EAX;
  undefined4 *puVar4;
  uint local_4;
  
  local_4 = 0;
  do {
    // Search for a matching entry in the game settings array (0x14 entries, each 2 words)
    if ((&DAT_01218e50)[local_4 * 2] == DAT_011f3910) {
      // If found and entry is already marked as "active" (bit 1 set), return early
      if ((local_4 < 0x14) && ((*(byte *)(&DAT_01218e54 + local_4 * 2) & 2) != 0)) {
        return;
      }
      goto LAB_004e2b72;
    }
    local_4 = local_4 + 1;
  } while (local_4 < 0x14);
  // If not found, use index 0x14 (beyond array, likely a sentinel)
  local_4 = 0x14;
LAB_004e2b72:
  // Clamp minimum value for some game settings (likely resolution or quality)
  if (DAT_012058d0 < 0xe) {
    DAT_012058d0 = 0xe;
  }
  if (0xe < DAT_00f15988) {
    DAT_00f15988 = 0xe;
  }
  _DAT_011f3a10 = 1;
  
  // Set width to 0xa8 (168) if below, clamp
  if (DAT_012058d4 < 0xa8) {
    DAT_012058d4 = 0xa8;
  }
  if (0xa7 < DAT_00f1598c) {
    DAT_00f1598c = 0xa8;
  }
  _DAT_011f3c78 = 0;
  
  // Set height to 0xbe (190) if below, clamp
  if (DAT_012058d4 < 0xbe) {
    DAT_012058d4 = 0xbe;
  }
  if (0xbd < DAT_00f1598c) {
    DAT_00f1598c = 0xbe;
  }
  _DAT_011f3cd0 = 0;
  
  // Set minimum value to 7
  if (DAT_012058d0 < 7) {
    DAT_012058d0 = 7;
  }
  if (7 < DAT_00f15988) {
    DAT_00f15988 = 7;
  }
  _DAT_011f39f4 = 1;
  
  // Set minimum value to 0x16 (22)
  if (DAT_012058d0 < 0x16) {
    DAT_012058d0 = 0x16;
  }
  if (0x16 < DAT_00f15988) {
    DAT_00f15988 = 0x16;
  }
  _DAT_011f3a30 = 1;
  
  // Set minimum value to 0x17 (23)
  if (DAT_012058d0 < 0x17) {
    DAT_012058d0 = 0x17;
  }
  if (0x17 < DAT_00f15988) {
    DAT_00f15988 = 0x17;
  }
  _DAT_011f3a34 = 8;
  
  // Set minimum value to 0x19 (25)
  if (DAT_012058d0 < 0x19) {
    DAT_012058d0 = 0x19;
  }
  if (0x19 < DAT_00f15988) {
    DAT_00f15988 = 0x19;
  }
  _DAT_011f3a3c = 5;
  
  // Set minimum value to 0x18 (24)
  if (DAT_012058d0 < 0x18) {
    DAT_012058d0 = 0x18;
  }
  if (0x18 < DAT_00f15988) {
    DAT_00f15988 = 0x18;
  }
  _DAT_011f3a38 = 0;
  
  // Set minimum value to 0xf (15)
  if (DAT_012058d0 < 0xf) {
    DAT_012058d0 = 0xf;
  }
  if (0xf < DAT_00f15988) {
    DAT_00f15988 = 0xf;
  }
  _DAT_011f3a14 = 0;
  
  // Call helper functions to initialize other systems
  FUN_00530c90(); // likely initializeAudioSettings
  FUN_00530a60(); // likely initializeVideoSettings
  
  // Handle some object state based on in_EAX (likely a handle or index)
  if ((in_EAX != 0xffffffff) && (in_EAX < 0x1000)) {
    iVar1 = in_EAX * 0x38;
    if ((&DAT_011a0f28 + iVar1 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar1] < 4)) {
      if (*(int *)(&DAT_011a0f44 + iVar1) != 0) {
        FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar1),0x210000); // likely setFlag
      }
      *(uint *)(&DAT_011a0f34 + iVar1) = *(uint *)(&DAT_011a0f34 + iVar1) & 0xfcad8fff | 0x210000;
      FUN_006189c0(); // likely updateObject
    }
  }
  
  // More initialization calls
  FUN_00530df0(); // likely initializeInputSettings
  FUN_00530ff0(); // likely initializeNetworkSettings
  
  // Allocate and initialize a structure (likely a color or vector)
  puVar4 = (undefined4 *)FUN_0060cd00(0xd,4,0,1,0); // likely allocateMemory
  uVar3 = DAT_00e2eff4;
  uVar2 = DAT_00e2b1a4;
  if (puVar4 != (undefined4 *)0x0) {
    *puVar4 = DAT_00e2eff4;
    puVar4[1] = uVar3;
    puVar4[2] = uVar2;
    puVar4[3] = uVar3;
    puVar4[4] = uVar2;
    puVar4[5] = uVar2;
    puVar4[6] = uVar3;
    puVar4[7] = uVar2;
    FUN_0060cde0(); // likely registerResource
  }
  
  FUN_00612e00(); // likely finalizeSettings
  
  // Reset some counters
  DAT_01219950 = 0;
  DAT_01219954 = 0;
  _DAT_012199e4 = 0;
  _DAT_012199e8 = 0;
  
  // Re-clamp some values with different defaults
  if (DAT_012058d4 < 0xa8) {
    DAT_012058d4 = 0xa8;
  }
  if (0xa7 < DAT_00f1598c) {
    DAT_00f1598c = 0xa8;
  }
  _DAT_011f3c78 = 0xf;
  
  if (DAT_012058d4 < 0xbe) {
    DAT_012058d4 = 0xbe;
  }
  if (0xbd < DAT_00f1598c) {
    DAT_00f1598c = 0xbe;
  }
  _DAT_011f3cd0 = 0xf;
  
  if (DAT_012058d0 < 0x17) {
    DAT_012058d0 = 0x17;
  }
  if (0x17 < DAT_00f15988) {
    DAT_00f15988 = 0x17;
  }
  _DAT_011f3a34 = 4;
  
  // Mark the entry as active (set bit 1) if found
  if (local_4 < 0x14) {
    (&DAT_01218e54)[local_4 * 2] = (&DAT_01218e54)[local_4 * 2] | 2;
  }
  return;
}