// FUNC_NAME: NetworkPacket::buildHeader
undefined4 __thiscall NetworkPacket::buildHeader(int this, undefined4 param_2, int param_3)
{
  uint computedSize;      // local_4 = (param_3 * 0x10 + 0xC) & 0xFFFF
  StreamManager* stream;  // DAT_01205590 -> global stream manager singleton
  uint writerTemp;        // uStack_10
  uint* blockPointer;     // puStack_14 -> points to local_8 (0x210)
  uint constant4;         // local_8 = 0x210 (packet type or flags)
  uint writerTemp2;       // uStack_1c (initially 0x597814, then overwritten to 2)
  int thisOffset2;        // iVar2 = this + 2

  computedSize = (param_3 * 0x10 + 0xC) & 0xFFFF;  // compute some field (e.g. length or CRC)
  writerTemp = 2;                                     // value to write (2 bytes)
  blockPointer = &constant4;                          // points to 0x210
  constant4 = 0x210;                                  // packet type identifier (0x210 = 528)
  writerTemp2 = 0x597814;                             // initial garbage? actually gets overwritten below
  // stream = *(StreamManager**)DAT_01205590; (implicitly dereferenced)
  
  // First virtual call: beginWrite() or reset()
  (*(code **)(*DAT_01205590 + 0x10))();
  
  // Write a 16-bit value (2) at offset this+2
  writerTemp2 = 2;
  thisOffset2 = this + 2;
  (*(code **)(*DAT_01205590 + 0x10))(thisOffset2, &writerTemp);
  
  // Write a 32-bit value (0x210) at offset this+4
  (*(code **)(*DAT_01205590 + 0x10))(this + 4, &blockPointer, 4);
  
  // Write a 16-bit value (2) at offset this+8
  (*(code **)(*DAT_01205590 + 0x10))(this + 8, &writerTemp2);
  
  // Copy 64 bytes from offset this+2 to offset this+0xC (iVar1 = 4, shifted by 4 => 64)
  (*(code **)(*DAT_01205590 + 0x10))(this + 0xC, thisOffset2, 4 << 4);
  
  return 0x4C;  // returns total packet header size (76 bytes)
}