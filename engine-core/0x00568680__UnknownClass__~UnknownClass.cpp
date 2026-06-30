// FUNC_NAME: UnknownClass::~UnknownClass
undefined4 * __thiscall UnknownClass::~UnknownClass(undefined4 *this, byte param_2)

{
  // Set vtable to this class's vtable (first initialization)
  *this = &PTR_FUN_00e3aa80;

  // Check if the member pointer at offset +0x0C is non-null, then call its destructor
  if (this[3] != 0) {
    UnknownClass::cleanupMember();  // FUN_00568740
  }

  // Switch vtable to base class vtable (for proper destruction chain)
  *this = &PTR_LAB_00e3aad0;

  // Reset some global flag (likely reference count or state)
  DAT_012234e0 = 0;

  // If the delete flag is set, call operator delete on this object
  if ((param_2 & 1) != 0) {
    operatorDelete(this);  // FUN_009c8eb0
  }
  return this;
}