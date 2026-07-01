// FUNC_NAME: PacketStream::PacketStream
void __fastcall PacketStream::PacketStream(undefined4 *this)

{
  // Set vtable pointer
  *this = &PTR_FUN_00d8ba60;
  // Set function pointers at offsets 0x3C and 0x48 (indices 0xF and 0x12)
  this[0xf] = &PTR_LAB_00d8ba50;
  this[0x12] = &PTR_LAB_00d8ba4c;
  // Initialize sub-object at offset 0x50 (this + 0x14 in dword units)
  FUN_004086d0(this + 0x14);
  FUN_00408310(this + 0x14);
  // Initialize sub-object at offset 0x58 (this + 0x16 in dword units)
  FUN_004086d0(this + 0x16);
  FUN_00408310(this + 0x16);
  // Global initialization call
  FUN_0046c640();
  return;
}