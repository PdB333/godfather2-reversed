// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass::constructor(undefined4 *self, byte param_2)

{
  *self = &PTR_FUN_00e3918c; // vtable setup
  self[2] = &PTR_LAB_00e391a0; // +0x8: some pointer
  self[3] = &PTR_LAB_00e391a8; // +0xC: some pointer
  FUN_00a0ea60(); // base class or subobject constructor
  if ((param_2 & 1) != 0) { // if bit 0 set (likely allocation flag)
    TlsGetValue(DAT_01139810); // get TLS slot value (probably for memory pool)
    FUN_00aa26e0(self, *(undefined2 *)(self + 1), 0xd); // destructor/dealloc call: (this, size at +0x4, 13=?)
  }
  return self;
}