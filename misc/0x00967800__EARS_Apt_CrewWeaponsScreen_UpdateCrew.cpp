// Xbox PDB: EARS_Apt_CrewWeaponsScreen_UpdateCrew
// FUNC_NAME: CrewManager::clearCrewMembersList
void __fastcall CrewManager::clearCrewMembersList(int this)
{
  int iVar1;
  int iVar2;
  byte bVar3;
  undefined1 local_25;
  uint local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint local_14;
  int local_10 [3];
  code *local_4;
  
  local_18 = this;
  FUN_005a04a0("ClearCrewMembersList",0,&DAT_00d8cdec,0);
  iVar1 = DAT_01129930;
  *(undefined4 *)(this + 0x10) = 0;  // +0x10: crew member count
  *(undefined4 *)(iVar1 + 0x2b4) = 0;  // +0x2b4: some global state
  *(undefined4 *)(iVar1 + 0x2b8) = 0;  // +0x2b8: some global state
  iVar2 = DAT_0112b9b4;
  local_1c = DAT_0112b9b4;
  if (*(int *)(DAT_0112b9b4 + 0x34) != -1) {
    *(int *)(iVar1 + 0x2b4) = *(int *)(DAT_0112b9b4 + 0x34);  // +0x34: some ID
  }
  local_14 = *(uint *)(iVar2 + 0x2c);  // +0x2c: crew member count
  local_24 = 0;
  if (local_14 != 0) {
    do {
      iVar1 = *(int *)(*(int *)(local_1c + 0x28) + local_24 * 4);  // +0x28: crew member array
      local_10[0] = 0;
      local_10[1] = 0;
      local_10[2] = 0;
      local_4 = (code *)0x0;
      local_20 = 0;
      FUN_006039d0(*(undefined4 *)(iVar1 + 0x38),&local_20,&local_25);  // +0x38: some handle
      if (local_20 != 0) {
        FUN_004d3d90(local_20);
      }
      bVar3 = FUN_008bcf60(iVar1);
      if (bVar3 < 4) {
        FUN_008bcf00(iVar1);
      }
      FUN_004d3b50(local_10);
      FUN_009674e0();
      if (local_10[0] != 0) {
        (*local_4)(local_10[0]);
      }
      local_24 = local_24 + 1;
    } while (local_24 < local_14);
  }
  FUN_005a04a0("ShowCrewMembersList",0,&DAT_00d8cdec,0);
  return;
}