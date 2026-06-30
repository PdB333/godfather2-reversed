// FUNC_NAME: BitStream::checkSequenceOrSkip
undefined4 __thiscall BitStream::checkSequenceOrSkip(int this, uint sequence)
{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int bitOffset;
  
  bitOffset = (int)sequence;
  if (bitOffset != -1) {
    do {
      // Get the next bit offset to read from
      piVar1 = (int *)(*(int *)(*(int *)this + 0xc) + bitOffset * 4);
      
      // If we're at the start of a packet, skip backwards if previous byte is continuation
      if ((bitOffset < 1) || (piVar2 = piVar1 + -1, ("$a $ a4A"[piVar1[-1] & 0x3f] & 0x80U) == 0)) {
        piVar2 = piVar1;
      }
      
      // Check if this is a "continue" marker (0x18) or if the sequence matches
      if ((((byte)*piVar2 & 0x3f) != 0x18) || ((*piVar2 >> 6 & 0x1ffU) != sequence)) {
        return 1; // Not found
      }
      
      // Calculate skip amount: if value is 0x1ffff (max skip), we need to continue
      iVar3 = (*piVar1 >> 6 & 0x3ffffU) - 0x1ffff;
    } while ((iVar3 != -1) && (bitOffset = bitOffset + 1 + iVar3, bitOffset != -1));
  }
  return 0; // Found matching sequence
}