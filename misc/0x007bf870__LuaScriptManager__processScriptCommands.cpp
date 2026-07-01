// FUNC_NAME: LuaScriptManager::processScriptCommands
void __thiscall LuaScriptManager::processScriptCommands(int this, undefined4 param_2)
{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  
  FUN_0046c710(param_2);  // Initialize script context
  FUN_0043aff0(param_2,0xeb6af905);  // Set script hash/identifier
  cVar2 = FUN_0043b120();  // Check if more commands available
  while (cVar2 == '\0') {
    FUN_0043b210();  // Advance to next command
    uVar3 = FUN_0043ab70();  // Get command type
    switch(uVar3) {
    case 0:  // Set float property
      FUN_0043b210();  // Skip command token
      uVar3 = FUN_0043ab90();  // Get float value
      FUN_004089b0(this + 0x6c,uVar3);  // Set float at +0x6c
      break;
    case 1:  // Set another float property
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_004089b0(this + 0x74,uVar3);  // Set float at +0x74
      break;
    case 2:  // Execute sub-script
      iVar4 = this + 0x88;
      FUN_0043b210(iVar4);  // Initialize sub-script context
      FUN_0043ad10(iVar4);  // Execute sub-script
      break;
    case 3:  // Set squared value
      iVar4 = FUN_0043b210();  // Get parameter pointer
      *(float *)(this + 0x7c) = *(float *)(iVar4 + 8) * *(float *)(iVar4 + 8);  // Square the value
      break;
    case 4:  // Set integer property
      FUN_0043b210();
      uVar3 = FUN_0043ab90();  // Get integer value
      FUN_00408980(this + 0x98,uVar3);  // Set int at +0x98
      break;
    case 5:  // Set another integer property
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_00408980(this + 0xa0,uVar3);  // Set int at +0xa0
      break;
    case 6:  // Set flags and handle special cases
      iVar4 = FUN_0043b210();
      uVar1 = *(uint *)(iVar4 + 8);  // Get flags value
      *(uint *)(this + 0x60) = uVar1;  // Store flags at +0x60
      if ((uVar1 & 1) != 0) {  // Check bit 0
        FUN_00408680(this + 0x50);  // Clear timer at +0x50
        FUN_00408680(this + 0x58);  // Clear timer at +0x58
      }
    }
    FUN_0043b1a0();  // Cleanup command
    cVar2 = FUN_0043b120();  // Check for more commands
  }
  if (DAT_0120e93c != 0) {  // Global data pointer check
    FUN_00408900(this + 0x3c,&DAT_0120e93c,0x8000);  // Copy global data to +0x3c
  }
  return;
}