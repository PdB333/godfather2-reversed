// FUNC_NAME: GodfatherGameManager::createMissionCharacterOrVehicle
void GodfatherGameManager::createMissionCharacterOrVehicle(void *param_1, undefined4 param_2, int *param_3)
{
  undefined4 uVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  undefined1 *local_10 [3];
  code *local_4;
  
  iVar4 = param_1;
  uVar1 = FUN_00445f00(param_1);  // Get current game state
  uVar1 = FUN_00405870(uVar1);    // Get some manager/table
  FUN_004d3bc0(uVar1);            // Start a script context
  FUN_004d57e0();                 // Clear errors
  FUN_004d4b00(local_10,&PTR_LAB_00d74bf8,param_2);  // Look up string for entity type
  FUN_004d5830(&DAT_00e2f0a0);    // Load/initialize resource
  puVar2 = local_10[0];
  if (local_10[0] == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e;       // Default empty string
  }
  iVar3 = FUN_00403a50(puVar2,0,0,0,0);  // Create entity from name
  *param_3 = iVar3;
  if (iVar3 != 0) {
    iVar3 = FUN_004025a0(iVar3);  // Get entity data block
    if (iVar3 == 0) {
      param_1 = 0xfe16702f;       // Error code?
    }
    else {
      param_1 = *(undefined4 *)(iVar3 + 0x2c);  // Get some field at +0x2C
    }
    FUN_00447d00(param_1);        // Initialize/register entity
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = iVar4 + 0x3c;      // Offset by 0x3C (some index/ID)
    }
    FUN_004035c0(*param_3,0x114,iVar4);  // Set parameter at offset 0x114
  }
  if (local_10[0] != (undefined1 *)0x0) {
    (*local_4)(local_10[0]);      // Possibly release string
  }
  return;
}