// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(undefined4 *this, byte allocFlag)
{
  // Set vtable pointers for multiple inheritance (offsets: 0x00, 0x3C, 0x48, 0x50)
  this[0] = &PTR_FUN_00d588f0;                 // +0x00: main vtable
  *(undefined4 **)((char *)this + 0x3C) = &PTR_LAB_00d588e0; // +0x3C: second base vtable
  *(undefined4 **)((char *)this + 0x48) = &PTR_LAB_00d588dc; // +0x48: third base vtable
  *(undefined4 **)((char *)this + 0x50) = &PTR_LAB_00d588d8; // +0x50: fourth base vtable

  // Call base class constructor
  BaseClass::BaseClass(); // FUN_006d6490

  // If allocFlag bit 0 is set, register object with memory manager (size 0xF4)
  if ((allocFlag & 1) != 0) {
    ObjectRegister(this, 0xf4); // FUN_0043b960 – likely adds to a memory tracking list
  }

  return this;
}