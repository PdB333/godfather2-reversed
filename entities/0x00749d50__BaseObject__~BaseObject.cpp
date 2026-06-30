// FUNC_NAME: BaseObject::~BaseObject
undefined4 * __thiscall BaseObject::destructor(BaseObject *this, byte deletionFlag)
{
  // Set vtable pointer (presumably to base class vtable)
  *this = &PTR_LAB_00d63090;
  // +0x68 (offset 0x1a * 4) is a pointer (likely to a string or child object)
  // Free it if non-null
  if (this[0x1a] != 0) {
    FUN_004daf90(this + 0x1a);
  }
  // Global static cleanup (e.g., reference counting)
  FUN_0080ea60();
  // If deletionFlag bit 0 is set, delete this object
  if ((deletionFlag & 1) != 0) {
    FUN_00624da0(this);
  }
  return this;
}