// FUNC_NAME: Core::hashOrRegisterString
void __thiscall hashOrRegisterString(int thisPtr, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5, undefined4 param6)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = *(uint *)(*(int *)(thisPtr + 0x18) + 0x2c); // +0x18: string table pointer, +0x2c: hash value or type flag
  uVar2 = uVar1 & 0xc0000000;
  if (uVar2 == 0) {
    // Type 0: direct bit shift lookup? (small strings or IDs)
    iVar3 = 1 << ((byte)(uVar1 >> 5) & 0x1f);
  }
  else if (uVar2 == 0x40000000) {
    // Type 1: pointer from table at offset 8
    iVar3 = *(int *)(uVar1 * 4 + 8);
  }
  else if (uVar2 == 0xc0000000) {
    // Type 2: pointer from table at offset 0x54
    iVar3 = *(int *)(uVar1 * 4 + 0x54);
  }
  else {
    // Fallback sentinel value
    iVar3 = -0x80000000;
  }
  // Call function at 0x54ebf0 with expanded parameters (likely string registration or hash retrieval)
  FUN_0054ebf0(param2, param3, 0x40322, iVar3, 0, 0, param4, param5, param6);
  return;
}