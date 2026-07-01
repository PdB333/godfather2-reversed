// FUNC_NAME: NetObject::unpackUpdate
void __thiscall NetObject::unpackUpdate(int thisPtr, undefined8 *packedData)
{
  // Copy 5 uint64 values from packed data into object fields at offsets +0x74 through +0x94
  *(undefined8 *)(thisPtr + 0x74) = packedData[0];  // +0x74: first uint64 field
  *(undefined8 *)(thisPtr + 0x7c) = packedData[1];  // +0x7c: second uint64 field
  *(undefined8 *)(thisPtr + 0x84) = packedData[2];  // +0x84: third uint64 field
  *(undefined8 *)(thisPtr + 0x8c) = packedData[3];  // +0x8c: fourth uint64 field
  *(undefined8 *)(thisPtr + 0x94) = packedData[4];  // +0x94: fifth uint64 field

  // Check bit 28 (0x10000000) in the 6th uint32 of packed data (offset 0x24 from packedData)
  if ((*(uint *)((int)packedData + 0x24) & 0x10000000) != 0) {
    // Set bit 0 in the flags field at +0xa0
    *(uint *)(thisPtr + 0xa0) = *(uint *)(thisPtr + 0xa0) | 1;  // +0xa0: flags field
  }
}