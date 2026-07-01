// FUNC_NAME: NetSession::NetSession
undefined4 * __thiscall NetSession::NetSession(NetSession *this, int allocateFlag)
{
  undefined4 allocResult;

  // If allocateFlag is non-zero, call allocation utility; else null
  if (allocateFlag == 0) {
    allocResult = 0;
  }
  else {
    allocResult = FUN_00481610(); // likely operator new or memory allocation
  }

  // Unknown initialization (maybe thread lock or reference counting)
  FUN_0064d390(1, 1);

  // Set base class vtable (first vtable, probably a common base)
  this->m_pBaseVTable = &PTR_LAB_00e317dc;  // +0x00
  // Clear field at offset +0x18 (index 6)
  this->m_someField18 = 0;                  // +0x18
  // Initialize with allocation result (could be a placement new or object init)
  FUN_00454a10(allocResult);
  // Set a flag at +0x24 to 1
  this->m_flag24 = 1;                       // +0x24

  // Override vtable with this class's vtable
  this->m_pVTable = &PTR_LAB_00d7e0b0;      // +0x00 (overwrites base vtable)
  // Clear field at +0x34 (index 13)
  this->m_someField34 = 0;                  // +0x34
  // Set pointer to another vtable/interface at +0x28
  this->m_pInterfaceVTable = &PTR_LAB_00d7e070; // +0x28
  // Set function pointer to LAB_008db480 at +0x30
  this->m_pStateFunction = &LAB_008db480;   // +0x30

  // Call some initialization routine (0 parameter)
  FUN_004a8ec0(0);
  // Store address of the interface vtable field at offset +0x14 (a self-reference?)
  this->m_pSelfRef14 = &this->m_pInterfaceVTable; // +0x14

  return this;
}