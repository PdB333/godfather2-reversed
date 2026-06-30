// FUNC_NAME: PoolAllocator::calculateAllocationSize
// Function address: 0x00669d40
// This function appears to compute the total size required for allocating a certain number (param_1) of fixed-size blocks (0x1c = 28 bytes each).
// It uses a bitmask for tracking used blocks and a base flag at offset +8 of the this object.
// param_1 == 2 is a special case: returns size based on the first field (number of blocks) and bitmask.
// For other param_1 (3..0x40), it loops calling an allocation function until success, then finalizes and returns the size.

__thiscall
int PoolAllocator::calculateAllocationSize(int param_1)
{
  int numBlocks;       // iVar1
  uint bitMask;        // uVar2
  int resultSize;      // iVar3
  bool isSpecial;      // bVar4
  int buffer[2];       // local_10 – uninitialized, used as temporary workspace
  int tempFlag;        // local_8 – uninitialized, used as flag

  numBlocks = param_1;
  // Special case: command == 2
  if (param_1 == 2) {
    // Dereference this pointer (in_EAX) to get first field: likely current block count
    numBlocks = this->m_blockCount;          // +0x00
    if (numBlocks == 0) {
      // Return 1 or 2 depending on a flag at +0x08
      return (this->m_useDoubleBase == 1 ? 2 : 1);
    }
    // Compute base size: (numBlocks - 1) * 0x1c (28 bytes per block)
    resultSize = (numBlocks - 1) * 0x1c;
    // Bitmask is stored at an array pointed to by this->m_bitmaskArray (+0x0C)
    bitMask = *(uint *)(this->m_bitmaskArray + (numBlocks - 1) * 4);  // array index at offset -4 + numBlocks*4
    // Count set bits in the bitmask (each bit corresponds to a sub-block)
    while (bitMask != 0) {
      resultSize++;
      bitMask >>= 1;
    }
    // Add the base flag (1 or 2) to the result
    return (this->m_useDoubleBase == 1 ? 2 : 1) + resultSize;
  }
  // Only accept commands 3..0x40 (since 0,1 and >0x40 return 0)
  if ((uint)(param_1 - 2) > 0x3e) {
    return 0;
  }
  // Check a global or static condition (FUN_006677e0) – possibly a mutex or ready flag
  if (FUN_006677e0() != 0) {
    return 0;
  }
  // Use temporary flag; assume it may be initialized from some global state
  isSpecial = (tempFlag == 1);
  if (isSpecial) {
    tempFlag = 0;
  }
  bitMask = (uint)isSpecial;
  // Main loop: attempt allocation via FUN_00666670 until it returns non-zero
  while (true) {
    // If the temporary buffer indicates empty (buffer[0] == 0), finalize and return
    if (buffer[0] == 0) {
      FUN_00665b40();    // Finalization function
      return bitMask + 1;
    }
    // Call allocation routine: FUN_00666670(buffer, numBlocks, buffer, &param_1)
    resultSize = FUN_00666670(buffer, numBlocks, buffer, &param_1);
    if (resultSize != 0) break;
    bitMask++;
  }
  // Finalize on success
  FUN_00665b40();
  return resultSize;
}