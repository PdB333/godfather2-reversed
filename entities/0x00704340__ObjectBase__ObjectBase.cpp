// FUNC_NAME: ObjectBase::ObjectBase
// Address: 0x00704340
// Constructor for a small object with three 4-byte fields. Initializes fields to zero,
// then calls a sub-initializer with an argument.
undefined4 * __thiscall ObjectBase::ObjectBase(undefined4 *this, undefined4 arg2, undefined4 arg3)
{
  // Initialize first three fields (offsets 0x00, 0x04, 0x08) to zero
  this[0] = 0;  // +0x00: field0
  this[1] = 0;  // +0x04: field1
  this[2] = 0;  // +0x08: field2

  // Sub-initializer call – likely initializes additional internal state using arg3
  FUN_007041d0(arg3);  // 0x007041d0: UnknownSubInit(arg3)

  return this;
}