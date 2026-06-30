// FUNC_NAME: EARSObject::EARSObject
// Function at 0x00455740: Constructor for EARSObject with multiple vtable pointers and built-in allocation flag
// Object layout (assuming 4-byte pointers):
//   +0x00: primary vtable pointer (PTR_FUN_00e31938)
//   +0x04: unknown (0x0C bytes to next vtable)
//   +0x08: unknown
//   +0x0C: secondary vtable pointer (PTR_LAB_00e31948)
//   +0x10: tertiary vtable pointer (PTR_FUN_00e31960)
// param_1: this pointer
// param_2: if bit 0 set, calls a cleanup function (likely operator delete) after initialization

EARSObject * __thiscall EARSObject::EARSObject(EARSObject *this, byte allocatedFlag)
{
  // Set up the three virtual function table pointers for this object
  this[0].vtable = &PTR_FUN_00e31938;   // +0x00: primary vtable
  this[3].vtable = &PTR_LAB_00e31948;   // +0x0C: secondary vtable
  this[4].vtable = &PTR_FUN_00e31960;    // +0x10: tertiary vtable

  // Initialize engine singletons or base subsystems
  FUN_004086d0(&DAT_01206940);  // Likely initializes static data at 0x01206940
  FUN_00408310(&DAT_0120ea7c);  // Likely initializes static data at 0x0120ea7c
  FUN_00564b90();                // Some global engine initialization
  FUN_004083d0();                // Additional engine initialization

  // If the allocated flag has bit 0 set, free this object (defensive cleanup)
  if ((allocatedFlag & 1) != 0) {
    FUN_009c8eb0(this);  // Operator delete or destructor-like cleanup
  }

  return this;
}