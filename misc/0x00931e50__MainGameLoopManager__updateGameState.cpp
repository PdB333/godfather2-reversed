// FUNC_NAME: MainGameLoopManager::updateGameState
void __fastcall MainGameLoopManager::updateGameState(void *this_ptr)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  int *piVar4;
  char *local_10;
  undefined4 local_c;
  undefined4 local_8;
  char local_4;
  
  cVar2 = FUN_00402080(&DAT_01206978);
  if (cVar2 != '\0') {
    FUN_004086d0(&DAT_01206978);
  }
  // Check for specific game modes (0x16 = Cuba, 0x11 = Miami/Queens)
  if ((DAT_01130548 == 0x16) || (DAT_01130548 == 0x11)) {
    // Execute frontend transition for Cuba or Miami maps
    FUN_00930e70(PTR_DAT_00e56738,PTR_s_cuba_str_miami_str_queens_str_00e5673c,0,
                 PTR_s_XFOWLER102_C8D726A_A11FA3D_v3_00e56740);
    DAT_00e5672c = 5;
  }
  else if (DAT_01130548 == 0x18) {
    // Handle New York map mode (0x18)
    // Get display strings from object offsets +0x84 and +0x74
    local_10 = *(char **)((int)this_ptr + 0x84);
    if (local_10 == (char *)0x0) {
      local_10 = &DAT_0120546e;
    }
    char *puVar5 = *(char **)((int)this_ptr + 0x74);
    if (puVar5 == (char *)0x0) {
      puVar5 = &DAT_0120546e;
    }
    uVar3 = FUN_00683280("FrontendMainLoop");
    piVar4 = (int *)FUN_006833d0(uVar3);
    FUN_0067c360(puVar5,local_10);
    iVar1 = *piVar4;
    uVar3 = FUN_00683280("GameMainLoop");
    (**(code **)(iVar1 + 0x14))(uVar3);
    DAT_00e5672c = 0x11;
    FUN_00401060();
    FUN_00401060();
  }
  local_c = DAT_01130338;
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c,0);
  return;
}