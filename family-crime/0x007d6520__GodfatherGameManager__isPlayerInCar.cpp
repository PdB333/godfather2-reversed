// FUNC_NAME: GodfatherGameManager::isPlayerInCar
bool GodfatherGameManager::isPlayerInCar(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = FUN_00798f50(0x35); // Get player entity (0x35 = player entity type)
  cVar1 = FUN_0079e920(uVar2); // Check if entity is valid/alive
  if (cVar1 != '\0') {
    cVar1 = FUN_007ab420(0x100000); // Check if entity has car flag (0x100000 = in vehicle)
    if (cVar1 != '\0') {
      iVar3 = FUN_007ab380(); // Get current vehicle
      return iVar3 != 0;
    }
  }
  return false;
}