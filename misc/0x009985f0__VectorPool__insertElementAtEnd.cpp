// FUNC_NAME: VectorPool::insertElementAtEnd
int __thiscall VectorPool::insertElementAtEnd(int *param_1, int param_2)
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  
  iVar2 = param_1[1]; // +0x04: current element count
  uVar1 = iVar2 + param_2; // new total elements needed
  if (iVar2 <= (int)uVar1) {
    uVar3 = param_1[2]; // +0x08: capacity (lower 30 bits) + flags (high 2 bits)
    if ((int)(uVar3 & 0x3fffffff) < (int)uVar1) {
      // Need to expand the pool
      uVar4 = (uVar3 & 0x3fffffff) * 2; // double capacity
      if ((int)uVar4 <= (int)uVar1) {
        uVar4 = uVar1; // but at least the new required size
      }
      iVar7 = *param_1; // +0x00: pointer to element data
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = -0x80000000; // set high bit (probably "owned allocation needed" flag)
      if (0 < (int)uVar4) {
        FUN_00aa4110(param_1, uVar4 & ((int)uVar4 < 0) - 1, 0xc0);
      }
      iVar8 = *param_1;
      if (0 < iVar2) {
        // Copy existing elements (each 0xC0 bytes)
        iVar5 = iVar7 - iVar8;
        param_2 = iVar2;
        do {
          if (iVar8 != 0) {
            FUN_00994fa0(iVar5 + iVar8); // element copy constructor at offset
          }
          iVar8 = iVar8 + 0xc0;
          param_2 = param_2 + -1;
        } while (param_2 != 0);
      }
      param_1[1] = iVar2;
      if (-1 < (int)uVar3) {
        // Free old allocation if it wasn't external memory
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(iVar7, (uVar3 & 0x3fffffff) * 0xc0, 0x17);
      }
    }
    // Fill new slots with default values (zero-initialization of 0xC0 byte elements)
    if (iVar2 < (int)uVar1) {
      puVar6 = (undefined4 *)(iVar2 * 0xc0 + 0x50 + *param_1);
      iVar7 = uVar1 - iVar2;
      do {
        if (puVar6 != (undefined4 *)&DAT_00000050) {
          puVar6[-0x14] = 0;
          puVar6[-0x13] = 0;
          puVar6[-0x12] = 0;
          *puVar6 = 0;
          puVar6[0x14] = 0;
          puVar6[0x15] = 0;
          puVar6[0x16] = 0;
          puVar6[0x17] = 0;
          puVar6[0x18] = 0;
          puVar6[0x19] = 0;
        }
        puVar6 = puVar6 + 0x30;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
  }
  param_1[1] = uVar1;
  return iVar2 * 0xc0 + *param_1; // Return pointer to where new elements were inserted
}