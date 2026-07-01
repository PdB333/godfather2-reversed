// Xbox PDB: EARS_Modules_GodfatherGameManager_GameParameters_SetAttributeMap
// FUNC_NAME: MultiplayerScenario::readScenarioAttributes
void __thiscall MultiplayerScenario::readScenarioAttributes(undefined4 *param_1, int *param_2)
{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  // Read PackedAttributes (bitfield) from the data source
  uVar2 = (**(code **)(*param_2 + 0x30))("PackedAttributes",0);
  // Extract individual bits/fields from the packed value
  param_1[9] = uVar2 & 7;          // +0x24: attribute bits 0-2
  param_1[8] = (int)uVar2 >> 3 & 7; // +0x20: attribute bits 3-5
  param_1[5] = (int)uVar2 >> 6 & 7; // +0x14: attribute bits 6-8
  param_1[7] = (int)uVar2 >> 9 & 0xf; // +0x1c: attribute bits 9-12
  param_1[10] = (int)uVar2 >> 0xd & 0xf; // +0x28: attribute bits 13-16
  param_1[0xb] = (int)uVar2 >> 0x15 & 7; // +0x2c: attribute bits 21-23
  *(byte *)((int)param_1 + 5) = (byte)(uVar2 >> 0x18) & 1; // +0x05: bit 24
  
  // Read various integer attributes
  uVar3 = (**(code **)(*param_2 + 0x30))("MatchTypeIndex",0);
  *param_1 = uVar3;                // +0x00: match type index
  
  uVar3 = (**(code **)(*param_2 + 0x30))("ModeIdx",0);
  param_1[2] = uVar3;              // +0x08: mode index
  
  uVar3 = (**(code **)(*param_2 + 0x30))("MapHash",0);
  param_1[4] = uVar3;              // +0x10: map hash
  
  uVar3 = (**(code **)(*param_2 + 0x30))("WeaponIdx",0);
  param_1[6] = uVar3;              // +0x18: weapon index
  
  uVar3 = (**(code **)(*param_2 + 0x30))("ScoreLimit",0);
  param_1[0xc] = uVar3;            // +0x30: score limit
  
  uVar3 = (**(code **)(*param_2 + 0x30))("RoundScore",0);
  param_1[0xd] = uVar3;            // +0x34: round score
  
  uVar3 = (**(code **)(*param_2 + 0x30))("DonWager",0);
  param_1[0xe] = uVar3;            // +0x38: don wager
  
  uVar3 = (**(code **)(*param_2 + 0x30))("DonFlow",0);
  param_1[0xf] = uVar3;            // +0x3c: don flow
  
  // Read boolean attributes
  uVar1 = (**(code **)(*param_2 + 0x28))("DonMode",0);
  *(undefined1 *)(param_1 + 0x13) = uVar1; // +0x4c: don mode flag
  
  uVar1 = (**(code **)(*param_2 + 0x28))("IsStrictNAT",0);
  *(undefined1 *)(param_1 + 1) = uVar1;    // +0x04: strict NAT flag
  
  uVar3 = (**(code **)(*param_2 + 0x30))("ModeRequested",0);
  param_1[3] = uVar3;              // +0x0c: requested mode
  
  // Clear remaining fields
  param_1[0x10] = 0;               // +0x40: reserved
  param_1[0x11] = 0;               // +0x44: reserved
  param_1[0x12] = 0;               // +0x48: reserved
  
  // Read version string (32 bytes max)
  (**(code **)(*param_2 + 0x20))("Version",(int)param_1 + 0x4d,0x20);
  *(undefined1 *)(param_1 + 0x1b) = 0; // +0x6c: null terminator for version string
  
  return;
}