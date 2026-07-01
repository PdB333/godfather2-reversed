// FUNC_NAME: UnknownBaseClass::Constructor
undefined4 __thiscall UnknownBaseClass::Constructor(undefined4 this, byte flags)
{
  // Call base constructor at 0x0090c540
  BaseClass::Constructor();

  // If the low bit of flags is set, call the destructor (placement delete) at 0x009c8eb0
  // This is a typical pattern for operator new placement or custom allocator: 
  // if construction fails, the allocator's deallocation function is called.
  if ((flags & 1) != 0) {
    UnknownBaseClass::Destructor(this);
  }

  return this;
}