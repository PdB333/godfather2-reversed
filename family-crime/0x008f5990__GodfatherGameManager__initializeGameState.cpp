// FUNC_NAME: GodfatherGameManager::initializeGameState
void __thiscall GodfatherGameManager::initializeGameState(int this, char param_2)

{
  char cVar1;
  char *pcVar2;
  undefined2 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  undefined4 uStack_470;
  char *local_46c;
  undefined2 *local_468;
  code *local_464;
  undefined4 local_460;
  undefined2 *local_458;
  undefined4 local_454;
  int local_450;
  code *pcStack_44c;
  undefined2 *local_448;
  code *local_444;
  int local_440;
  undefined2 *local_438;
  code *local_434;
  int local_430;
  undefined2 *local_428;
  code *local_424;
  undefined4 local_420;
  undefined4 uStack_41c;
  int local_410;
  undefined4 local_40c;
  undefined1 auStack_408 [4];
  code *local_404;
  
  local_438 = (undefined2 *)0x0;
  local_430 = 0;
  local_434 = (code *)0x0;
  local_448 = (undefined2 *)0x0;
  local_440 = 0;
  local_444 = (code *)0x0;
  local_428 = (undefined2 *)0x0;
  local_420 = 0;
  local_424 = (code *)0x0;
  local_468 = (undefined2 *)0x0;
  local_460 = 0;
  local_464 = (code *)0x0;
  FUN_004dc090(0x80,0); // Allocate memory for some structures
  FUN_004dc090(0x80,0);
  FUN_004dc090(0x80,0);
  FUN_004dc090(0x80,0);
  if (*(char *)(this + 0x2270) == '\0') { // Check if game state is already initialized
    FUN_008f49c0(&local_438); // Initialize some game state structures
    FUN_008f4aa0(&local_448);
    FUN_008f4b50(&local_428);
    if (param_2 == '\0') {
      FUN_008f5320(&local_468); // Initialize for single player
    }
    else {
      local_458 = (undefined2 *)0x0;
      local_450 = 0;
      local_454 = 0;
      FUN_008f5320(&local_458); // Initialize for multiplayer
      local_46c = (char *)0x0;
      FUN_006039d0(0x9b519275,&local_46c,(int)&uStack_470 + 3); // Load some resource by hash
      pcVar2 = local_46c;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      FUN_004dba80(local_46c,(int)pcVar2 - (int)(local_46c + 1)); // Process resource data
      FUN_004dbd90(local_410,0,local_40c);
      if (local_410 != 0) {
        (*local_404)(local_410);
      }
      puVar8 = local_458;
      if (local_458 == (undefined2 *)0x0) {
        puVar8 = &DAT_00e2df14;
      }
      uVar5 = FUN_004dbef0(puVar8);
      FUN_004dbd90(puVar8,0,uVar5);
      if (local_458 != (undefined2 *)0x0) {
        (*pcStack_44c)(local_458);
      }
    }
  }
  else {
    FUN_00698ec0(this + 0x2272); // Clean up existing state
    FUN_00698ec0(this + 0x2372);
    FUN_00698ec0(this + 0x2472);
    FUN_00698ec0(this + 0x2572);
  }
  puVar8 = local_468;
  if (local_468 == (undefined2 *)0x0) {
    puVar8 = &DAT_00e2df14;
  }
  puVar7 = local_428;
  if (local_428 == (undefined2 *)0x0) {
    puVar7 = &DAT_00e2df14;
  }
  puVar6 = local_448;
  if (local_448 == (undefined2 *)0x0) {
    puVar6 = &DAT_00e2df14;
  }
  puVar3 = local_438;
  if (local_438 == (undefined2 *)0x0) {
    puVar3 = &DAT_00e2df14;
  }
  FUN_00accc90(puVar3,puVar6,puVar7,puVar8); // Combine all state structures
  local_458 = (undefined2 *)0x0;
  local_454 = 0;
  local_450 = 0;
  iVar4 = (**(code **)**(undefined4 **)(this + 0x28))(0x40c,&local_458); // Allocate 0x40c bytes for game state
  local_420 = 0;
  uStack_41c = 0;
  if (iVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = FUN_00accdd0(auStack_408,&local_420,0x10000); // Initialize game state with 64KB buffer
  }
  *(undefined4 *)(this + 0x209c) = uVar5; // Store game state pointer
  if (uStack_470 != 0) {
    (*local_464)(uStack_470);
  }
  if (local_430 != 0) {
    (*local_424)(local_430);
  }
  if (local_450 != 0) {
    (*local_444)(local_450);
  }
  if (local_440 != 0) {
    (*local_434)(local_440);
  }
  return;
}