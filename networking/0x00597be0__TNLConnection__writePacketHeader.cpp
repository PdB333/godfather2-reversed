// FUNC_NAME: TNLConnection::writePacketHeader
undefined4 __fastcall TNLConnection::writePacketHeader(int thisPtr)
{
  int in_EAX;
  undefined4 local_8;
  undefined4 local_4;
  
  local_4 = 0x60; // packet header size (96 bytes)
  local_8 = 0x205; // packet type / flags (0x205 = reliable + some flag)
  
  // Write packet type/flags to offset 0
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr, &local_8, 2);
  
  // Write something to offset 2 (likely sequence number or ack)
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 2, &stack0xfffffff0, 2);
  
  // Write something at offset 4 (likely another flag or size)
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 4);
  
  // Write 0x40 bytes from source +0x1c to dest +8 (likely ghost list or state data)
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 8, *(undefined4 *)(in_EAX + 0x1c), 0x40);
  
  // Write various fields from source object to packet offsets
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 0x48, in_EAX + 0x18, 4); // +0x48 = some 4-byte field
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 0x4c, in_EAX + 4, 4);   // +0x4c = another field
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 0x50, in_EAX + 8, 4);   // +0x50
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 0x54, in_EAX + 0xc, 4); // +0x54
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 0x58, in_EAX + 0x10, 4);// +0x58
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 0x5c, in_EAX + 0x14, 4);// +0x5c
  
  return 0x60; // return packet header size
}