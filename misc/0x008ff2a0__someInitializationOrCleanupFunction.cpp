// FUNC_NAME: someInitializationOrCleanupFunction
undefined4 FUN_008ff2a0(void)

{
  uint uVar1;
  int local_c;
  uint local_8;
  undefined4 local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  FUN_008c73a0(&local_c);
  uVar1 = 0;
  if (local_8 != 0) {
    do {
      FUN_008fe990();
      uVar1 = uVar1 + 1;
    } while (uVar1 < local_8);
  }
  if (local_c != 0) {
    FUN_009c8f10(local_c);
  }
  return 1;
}