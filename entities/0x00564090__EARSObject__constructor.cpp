// FUNC_NAME: EARSObject::constructor
int __thiscall EARSObject::constructor(int this, byte flags)
{
  FUN_005640c0(); // base class constructor or initialization
  if ((flags & 1) != 0) {
    TlsGetValue(DAT_01139810); // get thread-local storage value
    FUN_00aa26e0(this, *(undefined2 *)(this + 4), 0x27); // allocate memory at offset +4 with size 0x27
  }
  return this;
}