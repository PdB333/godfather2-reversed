// FUNC_NAME: EARSFrameworkObject::~EARSFrameworkObject

void __thiscall EARSFrameworkObject::~EARSFrameworkObject(undefined4 *this)
{
  // Set vtable to base destructor vtable (PTR_FUN_00d5cec4)
  *this = &PTR_FUN_00d5cec4;

  // Release first child object: pointer at +0x3C, deleter at +0x48
  if (this[0xf] != 0) {
    ((void (*)(undefined4 *))(this[0x12]))(this[0xf]);
  }

  // Release second child object: pointer at +0x2C, deleter at +0x38
  if (this[0xb] != 0) {
    ((void (*)(undefined4 *))(this[0xe]))(this[0xb]);
  }

  // Switch to final vtable (PTR_FUN_00d5ce9c) before cleanup of member at +0x14
  *this = &PTR_FUN_00d5ce9c;
  FUN_0069a0e0(this[5]); // cleanup of m_member at +0x14
}