// FUNC_NAME: MemoryStream::writeBlock
undefined4 MemoryStream::writeBlock(int thisParam)
{
  int* currentBlock; // pointer to current block in stream
  int iVar1;
  undefined4* destPtr;
  int iVar3;
  int* blockIterator;
  int stepSize;
  
  currentBlock = *(int**)(thisParam + 0xc); // +0xc = current block pointer
  // Check if there is room in the stream
  if ((currentBlock < *(int**)(thisParam + 8)) && (currentBlock != (int*)0x0)) {
    if (*currentBlock == 4) {
      // Block is a free chunk (tag 4): reuse it
      iVar3 = currentBlock[1] + 0x10; // total size = blockSize + header size (0x10)
    }
    else {
      // Not free: try to get a new block from external manager
      iVar3 = FUN_00633990(thisParam); // validation/allocation function
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = currentBlock[1] + 0x10;
      }
      // Check if external manager needs compaction (free list full)
      if (*(uint*)(*(int*)(thisParam + 0x10) + 0x20) <= *(uint*)(*(int*)(thisParam + 0x10) + 0x24))
      {
        FUN_00627360(); // reallocation/compaction
      }
    }
    if (iVar3 == 0) goto LAB_0062c89d; // block allocation failed
  }
  else {
LAB_0062c89d:
    FUN_00627ac0(PTR_s_string_00e2a8ac); // assert/log error
  }
  
  iVar3 = *(int*)(thisParam + 0xc); // current block pointer again
  stepSize = 8; // element size: 4 bytes tag + 4 bytes data
  blockIterator = (int*)(iVar3 + 8); // move to next block (skip current tag?)
  if ((blockIterator < *(int**)(thisParam + 8)) && (blockIterator != (int*)0x0)) {
    if (*blockIterator == 4) {
      // Next block is also free? Or just a sanity check
      iVar3 = *(int*)(iVar3 + 0xc) + 0x10;
    }
    else {
      iVar1 = FUN_00633990(thisParam);
      if (iVar1 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int*)(iVar3 + 0xc) + 0x10;
      }
      if (*(uint*)(*(int*)(thisParam + 0x10) + 0x20) <= *(uint*)(*(int*)(thisParam + 0x10) + 0x24))
      {
        FUN_00627360();
      }
    }
    if (iVar3 != 0) goto LAB_0062c910; // allocation succeeded
  }
  stepSize = 2; // fallback step size? likely error
  FUN_00627ac0(PTR_s_string_00e2a8ac); // assert/log error
  
LAB_0062c910:
  // Zero out the region from current write pointer to end of block
  if (*(uint*)(thisParam + 8) < *(int*)(thisParam + 0xc) + 0x10U) {
    do {
      **(undefined4**)(thisParam + 8) = 0; // write 4 zero bytes
      *(int*)(thisParam + 8) = *(int*)(thisParam + 8) + stepSize; // advance by block size
    } while (*(uint*)(thisParam + 8) < *(int*)(thisParam + 0xc) + 0x10U);
  }
  
  iVar3 = *(int*)(thisParam + 0xc); // current block pointer
  destPtr = (undefined4*)(iVar3 + 0x10); // start of user data area
  *(undefined4**)(thisParam + 8) = destPtr; // update write pointer
  *destPtr = 3; // write tag 3 (active block)
  *(undefined4*)(iVar3 + 0x14) = 0; // zero next field
  *(int*)(thisParam + 8) = *(int*)(thisParam + 8) + stepSize; // advance past this block
  
  // Register a callback for deallocation (tag 3 -> free function at 0x0062c610)
  FUN_00625d70(thisParam, FUN_0062c610, 3);
  return 1; // success
}