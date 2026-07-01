// FUNC_NAME: SomeManager::formatAndSendString
void __thiscall formatAndSendString(int this, undefined4 param_2)
{
  float fVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 local_18;
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  // Calculate some value based on member fields at +0x1c and +0x38
  iVar2 = *(int *)(&DAT_00d8cca8 + *(int *)(this + 0x1c) * 4) * *(int *)(this + 0x38);
  local_10 = (undefined1 *)0x0;
  local_c = 0;
  fVar1 = (float)iVar2;
  local_8 = 0;
  local_4 = (code *)0x0;
  if (iVar2 < 0) {
    fVar1 = fVar1 + DAT_00e44578;
  }
  // Scale and round the value
  local_18 = (undefined4)(longlong)ROUND(fVar1 * DAT_00d5ef84);
  
  // Allocate memory or get string (FUN_00604000 likely a string allocation/format function)
  FUN_00604000(local_18, &local_10, 1);
  puVar3 = local_10;
  if (local_10 == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e;  // Fallback to empty string
  }
  // Copy string to destination (FUN_005c4660 likely a string copy function)
  FUN_005c4660(param_2, puVar3, 0x80, local_c);
  if (local_10 != (undefined1 *)0x0) {
    (*local_4)(local_10);  // Free allocated memory
  }
  return;
}