// FUNC_NAME: NetSession::NetSession
void __thiscall NetSession::NetSession(NetSession *this)
{
  // Set vtable pointer at offset 0
  this->vtable = &PTR_FUN_00d7cae8;
  // Set callback/state pointers at offset 0x3C and 0x48 (indices 0xf and 0x12 in dword units)
  this->callbacks_0x3C = &PTR_LAB_00d7cad8;
  this->somePtr_0x48 = &PTR_LAB_00d7cad4;
  // Construct base class or member object at offset 0x14 (sub-object at this+0x14)
  subObjectConstructor1(this + 0x14); // FUN_004086d0
  subObjectConstructor2(this + 0x14); // FUN_00408310
  // Global network initialization (e.g., packet pool setup)
  netGlobalInit(); // FUN_0046c640
}