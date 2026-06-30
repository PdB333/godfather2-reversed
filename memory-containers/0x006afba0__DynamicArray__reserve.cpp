// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *param_1, uint param_2)
{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if ((uint)param_1[2] < param_2) {
    puVar2 = (undefined4 *)FUN_009c8e80(param_2 * 8); // allocate new buffer (8 bytes per element)
    if (*param_1 != 0) {
      uVar3 = 0;
      puVar4 = puVar2;
      if (param_1[1] != 0) {
        do {
          if (puVar4 != (undefined4 *)0x0) {
            iVar1 = *param_1;
            *puVar4 = *(undefined4 *)(iVar1 + uVar3 * 8);
            puVar4[1] = *(undefined4 *)(iVar1 + 4 + uVar3 * 8);
          }
          uVar3 = uVar3 + 1;
          puVar4 = puVar4 + 2;
        } while (uVar3 < (uint)param_1[1]);
      }
      FUN_009c8f10(*param_1); // free old buffer
    }
    *param_1 = (int)puVar2;
    param_1[2] = param_2;
  }
  return;
}