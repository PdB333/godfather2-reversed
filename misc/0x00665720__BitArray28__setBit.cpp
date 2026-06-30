// FUNC_NAME: BitArray28::setBit
// Address: 0x00665720
// Role: Resets bitmap and sets a single bit (28 bits per element). Returns 0 on success, else error from check function.
// Structure offsets:
//   +0x00: int m_usedBlocks;  // number of blocks currently used (highest block index + 1)
//   +0x04: int m_numBlocks;   // allocated number of int blocks
//   +0x08: int m_flags;       // always cleared to 0
//   +0x0C: int* m_pBits;      // pointer to array of 28-bit-per-int blocks

int __thiscall BitArray28::setBit(int bitIndex)
{
  int blockIndex;
  int result;
  
  // Reset entire bitmap
  m_flags = 0;
  m_usedBlocks = 0;
  memset(m_pBits, 0, m_numBlocks * 4);
  
  blockIndex = bitIndex / 28;
  result = FUN_00667740(); // Check if operation is allowed (e.g., not full)
  if (result == 0) {
    m_usedBlocks = blockIndex + 1;
    m_pBits[blockIndex] |= 1 << (bitIndex % 28);
    result = 0;
  }
  return result;
}