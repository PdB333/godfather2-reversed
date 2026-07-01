// FUNC_NAME: NetReplicator::unpackUpdate
// Address: 0x008bd020
// Role: Deserializes a network update packet into a dynamic buffer of 0x2c-byte structures.
// Packet header (uint32 array):
// [0] : version/type (<5, with 4 being latest and special)
// [1] : some ID (stored at +0x14)
// [2] : hasPayload flag (if non-zero, copy from header+8)
// [3] : boolean flag (stored at +0x18 if not already set)
// [4..7] : reserved (skipped)
// Payload starts at [8] and consists of field0c * 0x2c bytes.

int __thiscall NetReplicator::unpackUpdate(void *this, int /*unused*/, unsigned int *packetData, int packetSize)
{
  void *dst;
  int result;

  if ((packetData != (unsigned int *)0x0) && (packetSize != 0)) {
    if (*packetData < 5) {                              // version check
      *(unsigned int *)((int)this + 0x14) = packetData[1];  // +0x14: ID
      if (*(char *)((int)this + 0x18) == '\0') {        // +0x18: bool, set only if not already true
        *(bool *)((int)this + 0x18) = packetData[3] != 0;
      }
      // Check if a specific game object exists (hash 0x637b907)
      result = FUN_008c74d0(0x637b907);
      if (result != 0) {
        FUN_008bd430(*(unsigned int *)((int)this + 0x14));
      }
      if (*packetData < 4) {
        FUN_008bcc30(0);                                 // no payload
      }
      else if (*packetData == 4) {
        FUN_008bcc30(packetData[2]);                     // hasPayload flag
        if (packetData[2] != 0) {
          if (*(int *)((int)this + 0xc) == 0) {          // +0x0c: element count
            dst = (void *)0x0;
          }
          else {
            dst = *(void **)((int)this + 8);              // +0x08: buffer pointer
          }
          _memcpy(dst, packetData + 8, *(int *)((int)this + 0xc) * 0x2c);
        }
        return 1;
      }
    }
    return 1;
  }
  // Reset / clear path
  *(unsigned int *)((int)this + 0x14) = 0;
  if (DAT_01129c4c != 0) {
    FUN_0093b0e0();
  }
  *(int *)((int)this + 0xc) = 0;
  FUN_009c8f10(*(void **)((int)this + 8));               // free buffer
  *(void **)((int)this + 8) = 0;
  *(int *)((int)this + 0x10) = 0;                        // +0x10: unknown field
  *(char *)((int)this + 0x18) = 0;
  return 1;
}