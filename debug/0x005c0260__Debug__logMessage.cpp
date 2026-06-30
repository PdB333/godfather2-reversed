// FUNC_NAME: Debug::logMessage
void Debug::logMessage(int param_1, undefined4 param_2, undefined1 param_3)
{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1 == 0) {
    param_1 = 0;
  }
  else {
    param_1 = param_1 + 4;
  }
  if (DAT_01205664 == 0) {
    iVar1 = FUN_005c4410(200,0);
    if (iVar1 == 0) {
      DAT_01205664 = 0;
    }
    else {
      DAT_01205664 = FUN_005c3070();
    }
    FUN_005c31d0();
  }
  FUN_005c28c0();
  puVar2 = (undefined4 *)FUN_005c2960();
  *puVar2 = param_2;
  puVar2[1] = param_1;
  *(undefined1 *)(puVar2 + 2) = param_3;
  return;
}