// FUNC_NAME: GodfatherGameManager::updateGameState
void GodfatherGameManager::updateGameState(void)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  FUN_0094fd30(); // likely updateGameTime or similar
  iVar3 = DAT_01223394; // g_pGameManager or similar singleton
  piVar1 = (int *)(DAT_01223394 + 0x4c); // +0x4c: some state pointer
  cVar2 = FUN_0040b8d0(*(undefined4 *)(DAT_01223394 + 0x4c)); // check if something is active
  if (cVar2 != '\0') {
    local_c = DAT_01206840; // some global data
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0); // clear or reset something
  }
  *(uint *)(iVar3 + 0x6c) = *(uint *)(iVar3 + 0x6c) | 0x20; // set flag at +0x6c
  *piVar1 = 0; // clear state pointer
  iVar3 = FUN_0079f9d0(); // get player object
  DAT_011307b4 = *(undefined1 *)(iVar3 + 0x274); // backup player state byte
  DAT_011307b6 = *(undefined1 *)(iVar3 + 0x276); // backup another byte
  DAT_011307b5 = *(undefined1 *)(iVar3 + 0x275); // backup another byte
  *(undefined1 *)(iVar3 + 0x274) = DAT_011307b4; // restore (no-op)
  *(undefined1 *)(iVar3 + 0x275) = *(undefined1 *)(iVar3 + 0x275); // no-op
  *(undefined1 *)(iVar3 + 0x276) = 1; // set player state to 1 (e.g., "active")
  FUN_0040eac0(1); // enable input or something
                    /* WARNING: Could not recover jumptable at 0x0094ff8a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*DAT_01129a74 + 0x28))(); // call virtual function at vtable+0x28 on some object
  return;
}