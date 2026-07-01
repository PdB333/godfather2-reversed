// FUNC_NAME: GodfatherGameManager::handleCredits
void __fastcall GodfatherGameManager::handleCredits(int this)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  FUN_00925610();
  if (this == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = this + 0x10;
  }
  FUN_005c0260(iVar3,&LAB_00925f10,1);
  piVar1 = DAT_01129924;
  if (*(char *)(this + 0x13a5) != '\0') {
    local_c = *(undefined4 *)(this + 0x9c);
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);
    return;
  }
  if (DAT_01129924 != (int *)0x0) {
    cVar2 = FUN_009c7920();
    if (cVar2 != '\0') {
      (**(code **)(*piVar1 + 4))();
    }
    FUN_009c82f0("credits.vp6",5,2);
  }
  return;
}