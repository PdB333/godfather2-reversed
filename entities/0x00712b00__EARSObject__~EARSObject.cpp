// FUNC_NAME: EARSObject::~EARSObject
undefined4* __thiscall EARSObject::~EARSObject(undefined4* this, byte deallocFlag)
{
  // Set vtable pointer to the class's vtable
  *this = &PTR_FUN_00d6198c;

  // Release a child object at offset 0x5C (0x17 * 4) if present
  if (this[0x17] != 0) {
    FUN_0071bc70(this[0x17]);  // likely release/delete child
    this[0x17] = 0;
  }

  // Call base class destructor
  FUN_0071e870();

  // If deallocation flag is set, free this memory
  if ((deallocFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}