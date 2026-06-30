// FUNC_NAME: MemoryAllocator::calculateAllocationSize
int __fastcall MemoryAllocator::calculateAllocationSize(uint *param_1)
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  // Align first size to minimum of 4 and round up to alignment
  uVar1 = param_1[1]; // +0x04: alignment for first dimension
  if (uVar1 < 4) {
    uVar1 = 4;
  }
  uVar3 = *param_1; // +0x00: first dimension count
  uVar2 = uVar1 - 1 & uVar3;
  if (uVar2 != 0) {
    uVar3 = uVar3 + (uVar1 - uVar2);
  }
  
  // Align second size to minimum of 4 and round up to alignment
  uVar1 = param_1[4]; // +0x10: alignment for second dimension
  if (uVar1 < 4) {
    uVar1 = 4;
  }
  uVar2 = param_1[3]; // +0x0C: second dimension count
  uVar4 = uVar1 - 1 & uVar2;
  if (uVar4 != 0) {
    uVar2 = uVar2 + (uVar1 - uVar4);
  }
  
  // Total size = (aligned first dimension * element size) + (aligned second dimension * element size) + header
  return param_1[2] * uVar3 + param_1[5] * uVar2 + 0x48; // +0x08: first element size, +0x14: second element size, +0x48: header overhead
}