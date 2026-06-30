// FUNC_NAME: EARSAllocator::allocateBlock
void EARSAllocator::allocateBlock(undefined4 param_1, undefined4 param_2)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 *unaff_ESI;
  int *unaff_EDI;
  
  uVar1 = unaff_EDI[1]; // +0x04: block flags/size
  uVar4 = uVar1 & 0x7ffffff8; // mask out low 3 bits (flags), get aligned size
  uVar2 = *(uint *)((int)unaff_EDI + uVar4 + 4); // next block header at offset
  *unaff_ESI = param_2; // store user data
  if ((uVar2 & 1) == 0) { // if next block is free (bit 0 clear)
    unaff_ESI[2] = uVar4; // +0x08: block size
    *(undefined1 *)(unaff_ESI + 5) = 4; // +0x14: block type = 4 (free?)
    unaff_ESI[1] = unaff_EDI; // +0x04: previous block pointer
    unaff_ESI[3] = unaff_EDI + 4; // +0x0C: pointer to data area
    unaff_ESI[4] = (unaff_EDI[1] & 0x7ffffff8U) - 0x10; // +0x10: remaining size
    *(undefined1 *)((int)unaff_ESI + 0x15) = 0; // +0x15: flag byte
    return;
  }
  uVar2 = unaff_EDI[1]; // re-read flags
  uVar3 = FUN_00647c90(); // allocate new memory block
  unaff_ESI[1] = unaff_EDI; // +0x04: previous block pointer
  if ((uVar1 & 2) != 0) { // if block has special flag (bit 1)
    *(byte *)(unaff_ESI + 5) = (-((uVar2 & 4) != 0) & 0xeU) + 2; // +0x14: compute type
    unaff_ESI[2] = *unaff_EDI + 0x10 + uVar4; // +0x08: size = prev size + 16 + aligned
    unaff_ESI[3] = unaff_EDI + 2; // +0x0C: data pointer
    unaff_ESI[4] = uVar3; // +0x10: new block pointer
    *(undefined1 *)((int)unaff_ESI + 0x15) = 1; // +0x15: flag byte = 1
    return;
  }
  *(byte *)(unaff_ESI + 5) = (-((uVar2 & 4) != 0) & 0xeU) + 2; // +0x14: compute type
  unaff_ESI[2] = uVar4; // +0x08: block size
  unaff_ESI[3] = unaff_EDI + 2; // +0x0C: data pointer
  unaff_ESI[4] = uVar3; // +0x10: new block pointer
  *(undefined1 *)((int)unaff_ESI + 0x15) = 0; // +0x15: flag byte = 0
  return;
}