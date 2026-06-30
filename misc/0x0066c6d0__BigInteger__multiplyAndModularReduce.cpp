// FUNC_NAME: BigInteger::multiplyAndModularReduce
int BigInteger::multiplyAndModularReduce(int *this, undefined8 *outResult)
{
  int iVar1;
  undefined4 uVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  size_t _Size;
  uint *puVar10;
  longlong lVar11;
  undefined8 uVar12;
  int local_2c;
  int local_20;
  int local_1c;
  undefined8 local_14;
  undefined8 local_c;
  
  iVar1 = *this; // +0x00: size (number of digits)
  uVar8 = iVar1 * 2 + 1;
  uVar7 = uVar8 & 0x8000003f;
  if ((int)uVar7 < 0) {
    uVar7 = (uVar7 - 1 | 0xffffffc0) + 1;
  }
  _Size = uVar8 + (0x80 - uVar7);
  puVar3 = (uint *)_calloc(4, _Size); // allocate product array
  if (puVar3 == (uint *)0x0) {
    return 0xfffffffe; // -2 = out of memory
  }
  
  // Multiply this->digits (this[3]) by themselves (squaring)
  // Using base 2^28 (0x10000000) representation
  if (0 < iVar1) {
    local_20 = 1;
    local_2c = 0;
    puVar6 = puVar3;
    local_1c = iVar1;
    do {
      lVar11 = __allmul(*(undefined4 *)(this[3] + local_2c), 0,
                        *(undefined4 *)(this[3] + local_2c), 0);
      uVar4 = (uint)(lVar11 + (ulonglong)*puVar6);
      uVar7 = uVar4 >> 0x1c | (int)(lVar11 + (ulonglong)*puVar6 >> 0x20) * 0x10;
      *puVar6 = uVar4 & 0xfffffff; // store low 28 bits
      
      uVar2 = *(undefined4 *)(local_2c + this[3]);
      puVar10 = puVar6;
      for (iVar9 = local_20; puVar10 = puVar10 + 1, iVar9 < iVar1; iVar9 = iVar9 + 1) {
        uVar12 = __allmul(*(undefined4 *)(this[3] + iVar9 * 4), 0, uVar2, 0);
        uVar12 = __allmul(uVar12, 2, 0); // multiply by 2 for symmetric term
        uVar4 = (uint)uVar12 + *puVar10;
        uVar5 = uVar4 + uVar7;
        uVar7 = uVar5 >> 0x1c |
                ((int)((ulonglong)uVar12 >> 0x20) + (uint)CARRY4((uint)uVar12, *puVar10) +
                (uint)CARRY4(uVar4, uVar7)) * 0x10;
        *puVar10 = uVar5 & 0xfffffff;
      }
      // Propagate remaining carries
      for (; uVar7 != 0; uVar7 = uVar5 >> 0x1c | (uint)CARRY4(uVar4, uVar7) << 4) {
        uVar4 = *puVar10;
        uVar5 = uVar4 + uVar7;
        *puVar10 = uVar5 & 0xfffffff;
        puVar10 = puVar10 + 1;
      }
      local_2c = local_2c + 4;
      puVar6 = puVar6 + 2;
      local_20 = local_20 + 1;
      local_1c = local_1c + -1;
    } while (local_1c != 0);
  }
  
  // Trim leading zeros from result
  if (0 < (int)uVar8) {
    puVar6 = puVar3 + iVar1 * 2;
    do {
      if (*puVar6 != 0) break;
      uVar8 = uVar8 - 1;
      puVar6 = puVar6 + -1;
    } while (0 < (int)uVar8);
  }
  
  // Prepare result structure: size and data pointer
  local_14 = CONCAT44(_Size, uVar8); // result size
  local_c = ZEXT48(puVar3) << 0x20; // data pointer
  lVar11 = local_c;
  uVar12 = *outResult; // previous size
  local_c._4_4_ = (void *)((ulonglong)outResult[1] >> 0x20); // previous data pointer
  
  *outResult = local_14; // store new (size, capacity)
  outResult[1] = lVar11; // store new data pointer
  
  // Free old buffer if it existed
  if (local_c._4_4_ != (void *)0x0) {
    local_14._0_4_ = (int)uVar12;
    _memset(local_c._4_4_, 0, (int)local_14 * 4);
    _free(local_c._4_4_);
  }
  return 0;
}