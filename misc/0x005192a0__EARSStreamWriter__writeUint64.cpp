// FUNC_NAME: EARSStreamWriter::writeUint64
void __thiscall EARSStreamWriter::writeUint64(int *this, uint32_t high, uint32_t low)
{
  int *streamPtr;
  int streamBase;
  undefined8 *alignedPtr;
  
  streamBase = *this;
  // Write the vtable pointer for the stream writer (offset +0x14)
  **(undefined4 **)(streamBase + 0x14) = &PTR_FUN_01125158;
  streamPtr = (int *)(streamBase + 0x14);
  *streamPtr = *streamPtr + 4;
  
  // Align the write pointer to 4-byte boundary
  streamBase = *this;
  alignedPtr = (undefined8 *)((*(int *)(streamBase + 0x14) + 3U) & 0xfffffffc);
  *(undefined8 **)(streamBase + 0x14) = alignedPtr;
  
  // Write the 64-bit value (high and low combined)
  *alignedPtr = CONCAT44(high, low);
  
  // Advance the write pointer by 8 bytes
  *(int *)(streamBase + 0x14) = *(int *)(streamBase + 0x14) + 8;
}