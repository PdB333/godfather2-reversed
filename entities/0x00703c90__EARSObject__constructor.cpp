// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte allocFlag)
{
  // Call base class constructor (likely EARSObjectBase or similar)
  EARSObjectBase::constructor();

  // If the allocation flag has the low bit set, perform additional initialization
  // 0x78 = 120 bytes – likely size of a sub-object or memory block to be cleared/constructed
  if ((allocFlag & 1) != 0) {
    // FUN_0043b960 is a helper that initializes a block of 'this' of given size (e.g., memset or placement new)
    // In many EARS constructors, this is used for optional member allocation.
    EARSObject::initSubObject(this, 0x78); // 0x78 bytes
  }

  return this;
}