// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *param_1, uint param_2)
{
  int iVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  int iVar4;
  uint uVar5;
  
  if ((uint)param_1[2] < param_2) {
    puVar2 = (undefined8 *)FUN_009c8e80(param_2 * 0xc); // allocate new buffer (0xc = 12 bytes per element)
    if (*param_1 != 0) {
      uVar5 = 0;
      if (param_1[1] != 0) {
        iVar4 = 0;
        puVar3 = puVar2;
        do {
          iVar1 = *param_1;
          if (puVar3 != (undefined8 *)0x0) {
            *puVar3 = *(undefined8 *)(iVar1 + iVar4); // copy 8 bytes
            *(undefined4 *)(puVar3 + 1) = *(undefined4 *)((undefined8 *)(iVar1 + iVar4) + 1); // copy 4 bytes
          }
          uVar5 = uVar5 + 1;
          iVar4 = iVar4 + 0xc;
          puVar3 = (undefined8 *)((int)puVar3 + 0xc);
        } while (uVar5 < (uint)param_1[1]);
      }
      FUN_009c8f10(*param_1); // free old buffer
    }
    *param_1 = (int)puVar2;
    param_1[2] = param_2; // update capacity
  }
  return;
}