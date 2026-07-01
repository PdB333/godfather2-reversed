// FUNC_NAME: GodfatherGameManager::spawnPlayerOrSomething
void __fastcall GodfatherGameManager::spawnPlayerOrSomething(undefined4 param_1)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  cVar1 = FUN_00481660(); // likely isGameActive() or isInGame()
  if (cVar1 != '\0') {
    iVar2 = FUN_009c8e50(0x38); // allocate memory of size 0x38 (56 bytes) - probably for a player/entity
    if (iVar2 != 0) {
      uVar3 = FUN_0089c080(param_1); // construct the object at allocated memory, returns handle/pointer
      FUN_00481690(uVar3); // register or add to game world
      return;
    }
    FUN_00481690(0); // failed allocation, pass null
  }
  return;
}