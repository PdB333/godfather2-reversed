// FUNC_NAME: HashTable::addOrRehash
uint HashTable::addOrRehash(uint element)
{
  int *piVar1;
  uint *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int in_EAX;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  
  // +0x08: count
  *(int *)(this + 0x8) = *(int *)(this + 0x8) + 1;
  piVar1 = (int *)(in_EAX + 0xc);
  FUN_00657bf0(*(int *)(in_EAX + 0xc) + 1);
  *piVar1 = *piVar1 + 1;
  piVar3 = (int *)(*(int *)(in_EAX + 0x14) + -4 + *piVar1 * 4);
  if (piVar3 != (int *)0x0) {
    *piVar3 = element;
  }
  uVar10 = *(uint *)(in_EAX + 0x18);
  iVar4 = *piVar1;
  puVar2 = (uint *)(in_EAX + 0x18);
  if ((int)uVar10 / 2 < iVar4) {
    // +0x18: capacity. Rehash needed if current count > half capacity
    uVar10 = iVar4 * 4 - 1;
    FUN_00657bf0(uVar10);
    if (*puVar2 < uVar10) {
      *puVar2 = uVar10;
    }
    else if ((uVar10 < *puVar2) && (*puVar2 = uVar10, uVar10 == 0)) {
      // +0x20: buckets array
      (*(code *)PTR__free_00f0cd8c)(*(undefined4 *)(in_EAX + 0x20));
      *(undefined4 *)(in_EAX + 0x20) = 0;
      *(undefined4 *)(in_EAX + 0x1c) = 0; // +0x1c: likely bucketCount
    }
    uVar8 = 0;
    if (0 < (int)*puVar2) {
      do {
        // Clear new buckets
        *(undefined4 *)(*(int *)(in_EAX + 0x20) + uVar8 * 4) = 0;
        uVar8 = uVar8 + 1;
      } while ((int)uVar8 < (int)*puVar2);
    }
    // Rehash all existing elements into new buckets
    element = 0;
    if (0 < iVar4) {
      do {
        iVar5 = *(int *)(*(int *)(in_EAX + 0x14) + element * 4);
        // Hash function using various fields from element structure
        uVar10 = ((((uint)*(ushort *)(iVar5 + 0x102) ^ *(uint *)(iVar5 + 0x108) << 8) * 8 ^
                  *(uint *)(iVar5 + 0x10c)) << 5 ^ *(uint *)(iVar5 + 0x108) >> 0x10 ^
                 *(uint *)(iVar5 + 0x104)) % *puVar2; // +0x102, +0x104, +0x108, +0x10c: hash key fields
        iVar6 = *(int *)(in_EAX + 0x20);
        iVar7 = *(int *)(iVar6 + uVar10 * 4);
        // Linear probing for collision resolution
        while (iVar7 != 0) {
          uVar10 = uVar10 + 1;
          if (*puVar2 <= uVar10) {
            uVar10 = 0;
          }
          iVar7 = *(int *)(iVar6 + uVar10 * 4);
        }
        *(int *)(iVar6 + uVar10 * 4) = iVar5;
        element = element + 1;
      } while ((int)element < iVar4);
      return element;
    }
  }
  else {
    // No rehash needed, add single element to existing bucket
    iVar4 = *(int *)(*(int *)(in_EAX + 0x14) + -4 + iVar4 * 4);
    uVar9 = (((uint)*(ushort *)(iVar4 + 0x102) ^ *(uint *)(iVar4 + 0x108) << 8) * 8 ^
            *(uint *)(iVar4 + 0x10c)) << 5 ^ *(uint *)(iVar4 + 0x108) >> 0x10 ^
            *(uint *)(iVar4 + 0x104);
    uVar8 = uVar9 / uVar10;
    uVar9 = uVar9 % uVar10;
    iVar5 = *(int *)(in_EAX + 0x20);
    iVar6 = *(int *)(iVar5 + uVar9 * 4);
    while (iVar6 != 0) {
      uVar9 = uVar9 + 1;
      if (uVar10 <= uVar9) {
        uVar9 = 0;
      }
      iVar6 = *(int *)(iVar5 + uVar9 * 4);
    }
    *(int *)(iVar5 + uVar9 * 4) = iVar4;
  }
  return uVar8;
}