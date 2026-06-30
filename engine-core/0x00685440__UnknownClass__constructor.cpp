// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass::constructor(UnknownClass *this, byte flags)
{
  // Set vtables for this object (first base class)
  // vtable at offset 0x00
  *(void **)this = &PTR_FUN_00d58928;
  // vtable at offset 0x3C (param_1[0xf])
  *(void **)((char *)this + 0x3C) = &PTR_LAB_00d58918;
  // vtable at offset 0x48 (param_1[0x12])
  *(void **)((char *)this + 0x48) = &PTR_LAB_00d58914;

  // Call base class 1 constructor (likely initializes fields and sets another vtable)
  BaseClass1Constructor();

  // Overwrite vtables with second set (for base class 2 or derived class)
  *(void **)this = &PTR_FUN_00d5888c;
  *(void **)((char *)this + 0x3C) = &PTR_LAB_00d5887c;
  *(void **)((char *)this + 0x48) = &PTR_LAB_00d58878;

  // Call base class 2 constructor
  BaseClass2Constructor();

  // If the low bit of flags is set, free the object (likely for placement new with dynamic allocation)
  if ((flags & 1) != 0) {
    OperatorDelete(this, 0x74);
  }

  return this;
}