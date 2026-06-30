// FUNC_NAME: SomeArrayBasedContainer::tryGetElementByIndex
undefined1 __thiscall FUN_005e7840(uint param_1, undefined4 *param_2)
{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  int unaff_ESI;
  
  bVar1 = *(byte *)(unaff_ESI + 0x1c);
  uVar6 = 0;
  // Check if index is within bounds (some XOR-based guard, possibly for obfuscation or error detection)
  if (((((param_1 ^ 0xad103100) < (uint)bVar1) && (bVar1 != 0)) && ((byte)param_1 < bVar1)) &&
     // Dereference the element pointer from the array at offset +0x04 (base pointer to array data)
     (iVar2 = *(int *)(unaff_ESI + 4 + (param_1 & 0xff) * 4), iVar2 != 0)) {
    // Copy the element's data (16 bytes) starting at offset +0x40 within the element to output buffer
    uVar3 = *(undefined4 *)(iVar2 + 0x44);
    uVar4 = *(undefined4 *)(iVar2 + 0x48);
    uVar5 = *(undefined4 *)(iVar2 + 0x4c);
    *param_2 = *(undefined4 *)(iVar2 + 0x40);
    param_2[1] = uVar3;
    param_2[2] = uVar4;
    param_2[3] = uVar5;
    uVar6 = 1;
  }
  return uVar6;
}