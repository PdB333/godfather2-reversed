// FUNC_NAME: EntityDataManager::deserializeEntityProperties
void __thiscall EntityDataManager::deserializeEntityProperties(int param_1, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_0046c710(param_2);  // StreamReader::beginReading
  FUN_0043aff0(param_2,0x1f1418c3);  // Read signature/magic
  cVar1 = FUN_0043b120();  // Check for more data
  while (cVar1 == '\0') {
    FUN_0043b210();  // Read property type header
    uVar2 = FUN_0043ab70();  // Get property type ID
    switch(uVar2) {
    case 0:
      FUN_0043b210();  // Skip type header
      uVar2 = FUN_0043ab90();  // Read string value
      FUN_004089b0(param_1 + 100,uVar2);  // SetStringProperty(param_1+0x64, string)
      break;
    case 1:
      FUN_0043b210();  // Skip type header
      uVar2 = FUN_0043ab90();  // Read string value
      FUN_00408980(param_1 + 0x6c,uVar2);  // SetFloatProperty(param_1+0x6c, string)
      break;
    case 2:
      FUN_0043b210();  // Skip type header
      uVar2 = FUN_0043ab90();  // Read string value
      FUN_00408980(param_1 + 0x74,uVar2);  // SetFloatProperty(param_1+0x74, string)
      break;
    case 3:
      iVar3 = param_1 + 0x54;
      FUN_0043b210(iVar3);  // Read vector/color into iVar3
      FUN_0043ad10(iVar3);  // Process vector
      break;
    case 4:
      iVar3 = FUN_0043b210();  // Read integer value
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(iVar3 + 8);  // SetIntProperty(param_1+0x50, int)
    }
    FUN_0043b1a0();  // Advance to next property
    cVar1 = FUN_0043b120();  // Check for more data
  }
  if ((((*(int *)(param_1 + 0x54) == 0) && (*(int *)(param_1 + 0x58) == 0)) &&
      (*(int *)(param_1 + 0x5c) == 0)) && (*(int *)(param_1 + 0x60) == 0)) {
    FUN_004088c0(param_1 + 0x3c);  // ClearVector(param_1+0x3c) - reset position
  }
  return;
}