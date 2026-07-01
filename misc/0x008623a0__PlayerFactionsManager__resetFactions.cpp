// FUNC_NAME: PlayerFactionsManager::resetFactions
void __fastcall PlayerFactionsManager__resetFactions(int this)
{
  int iVar1;
  undefined4 local_1c;
  undefined ***local_18;
  undefined1 local_14;
  undefined **local_10;
  undefined8 local_c;
  undefined4 local_4;
  
  *(undefined4 *)(this + 0xf20) = 0; // +0xf20: some faction-related flag/counter
  local_10 = &PTR_LAB_00d7584c; // pointer to some static data
  iVar1 = FUN_00471610(); // likely getGameManager or getPlayerManager
  local_c = *(undefined8 *)(iVar1 + 0x30); // +0x30: some player data (e.g., player color/info)
  local_4 = *(undefined4 *)(iVar1 + 0x38); // +0x38: additional player data
  local_1c = DAT_0112dfb8; // global flag or state
  local_18 = &local_10;
  local_14 = 0;
  FUN_0043c6f0(4, &local_1c, 0); // likely send event, log, or reset state with type 4
  return;
}