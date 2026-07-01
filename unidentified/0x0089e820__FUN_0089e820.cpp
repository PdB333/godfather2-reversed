// FUNC_NAME: unknown::clearItems
void __fastcall clearItems(int *param_1)

{
  int iVar1;
  
  iVar1 = 4;
  do {
    if (*param_1 != 0) {
      FUN_004daf90(param_1); // likely free or release
      *param_1 = 0;
    }
    param_1[2] = 0;
    param_1 = param_1 + 3;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}