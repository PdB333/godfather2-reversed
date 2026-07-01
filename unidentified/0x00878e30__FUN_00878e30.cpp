// FUNC_NAME: UnknownClass::checkBitmaskOrIdMatch
undefined1 __thiscall checkBitmaskOrIdMatch(int this, int param_2, undefined4 *param_3)
{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = 0;
  piVar2 = (int *)(this + 0xed4); // +0xed4: array of 4 structs (each 12 bytes: id, ?, bitmask)
  while( true ) {
    if (*piVar2 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *piVar2 + -0x48; // subtract 0x48 from id
    }
    // Check if the adjusted id matches param_2 AND the bitmask (piVar2[2]) has the bit set for *param_3
    if ((iVar1 != param_2) && ((piVar2[2] & 1 << ((byte)*param_3 & 0x1f)) != 0)) break;
    uVar3 = uVar3 + 1;
    piVar2 = piVar2 + 3; // advance to next struct (3 ints = 12 bytes)
    if (3 < uVar3) {
      return 1; // all 4 entries checked, no match found
    }
  }
  return 0; // match found
}