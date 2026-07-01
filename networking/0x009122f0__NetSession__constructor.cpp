// FUNC_NAME: NetSession::constructor
undefined4 * __fastcall NetSession::constructor(undefined4 *this)
{
  // Base class constructor call
  FUN_005bf9b0();
  
  // Initialize vtable pointers at +0x4C (+0x13*4) and +0x50 (+0x14*4)
  this[0x13] = &PTR_FUN_00e2f19c;
  this[0x14] = 1;            // +0x50: some counter or flag
  this[0x15] = 0;            // +0x54: initialized to 0
  this[0x16] = &PTR_LAB_00d840a0;  // +0x58: vtable pointer
  
  // Store global pointer to this instance
  DAT_0112981c = this;       // Global NetSession* pointer
  
  // Main vtable pointer at offset 0
  *this = &PTR_FUN_00d840e0;
  
  // Additional vtable pointer at +0x10
  this[4] = &PTR_LAB_00d840b8;
  
  // Update vtable pointers to derived class vtables
  this[0x13] = &PTR_LAB_00d840a8; // +0x4C: vtable override
  this[0x16] = &PTR_LAB_00d840a4; // +0x58: vtable override
  
  this[0x17] = 0;            // +0x5C: some field initialized to 0
  
  // Check global DAT_01130460 (likely some allocated buffer)
  if (DAT_01130460 != 0) {
    // FUN_00408900 is likely memcpy or similar - copies 0x8000 bytes from DAT_01130460 to this+0x4C
    FUN_00408900(this + 0x13, &DAT_01130460, 0x8000);
  }
  
  return this;
}