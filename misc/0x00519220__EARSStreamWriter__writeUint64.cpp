// FUNC_NAME: EARSStreamWriter::writeUint64
void __thiscall EARSStreamWriter::writeUint64(int *this, uint32_t high, uint32_t low)
{
  int *bufferPtr;
  int bufferBase;
  undefined8 *alignedPtr;
  
  bufferBase = *this;
  // Write vtable pointer for the stream writer (likely for serialization type info)
  **(undefined4 **)(bufferBase + 0x14) = &PTR_FUN_01125144; // +0x14: current write pointer
  bufferPtr = (int *)(bufferBase + 0x14);
  *bufferPtr = *bufferPtr + 4; // Advance write pointer by 4 bytes
  
  // Align to 4-byte boundary (round up to next multiple of 4)
  bufferBase = *this;
  alignedPtr = (undefined8 *)((*(int *)(bufferBase + 0x14) + 3U) & 0xfffffffc);
  *(undefined8 **)(bufferBase + 0x14) = alignedPtr;
  
  // Write the 64-bit value (high and low 32-bit parts concatenated)
  *alignedPtr = CONCAT44(low, high); // low in lower 32 bits, high in upper 32 bits
  
  // Advance write pointer by 8 bytes (size of uint64)
  *(int *)(bufferBase + 0x14) = *(int *)(bufferBase + 0x14) + 8;
}