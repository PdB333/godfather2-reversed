// FUNC_NAME: FUN_0068cd00
void __fastcall FUN_0068cd00(int param_1)
{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14;
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  if (DAT_0112982c != 0) {
    local_1c = DAT_01129aa0;
    local_18 = 0;
    local_14 = 0;
    FUN_00408a00(&local_1c,0);
    local_10 = (undefined1 *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (code *)0x0;
    uVar1 = FUN_0068cc40(&local_10);
    puVar2 = local_10;
    if (local_10 == (undefined1 *)0x0) {
      puVar2 = &DAT_0120546e;
    }
    FUN_00983120(puVar2,0,uVar1);
    *(undefined4 *)(param_1 + 0x10) = 3;
    if (local_10 != (undefined1 *)0x0) {
      (*local_4)(local_10);
    }
  }
  return;
}