// FUNC_NAME: StringTable::insertOrFind
undefined2 ** StringTable::insertOrFind(undefined2 **param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  undefined2 *local_10;
  undefined4 uStack_c;
  code *local_4;
  
  *param_1 = (undefined2 *)0x0;
  param_1[2] = (undefined2 *)0x0;
  param_1[1] = (undefined2 *)0x0;
  uVar2 = FUN_004dbef0(param_2);
  FUN_004dba00(param_2,uVar2);
  cVar1 = FUN_00698f20(param_3,&local_10,&DAT_01129f9c,param_1,1);
  if (local_10 != (undefined2 *)0x0) {
    (*local_4)(local_10);
  }
  if (cVar1 == '\\0') {
    FUN_004dba80(&DAT_00e2f044,0);
    if (param_1 != &local_10) {
      puVar3 = local_10;
      if (local_10 == (undefined2 *)0x0) {
        puVar3 = &DAT_00e2df14;
      }
      FUN_004dbb10(puVar3,0,uStack_c);
    }
    if (local_10 != (undefined2 *)0x0) {
      (*local_4)(local_10);
    }
  }
  return param_1;
}