// FUNC_NAME: SomeClass::constructor
int __thiscall SomeClass::constructor(int this, byte flags)
{
  undefined4 *vtablePtr;
  
  if (this == 0) {
    vtablePtr = (undefined4 *)0x0;
  }
  else {
    vtablePtr = (undefined4 *)(this + 0x20);
  }
  *vtablePtr = &PTR_LAB_00d580dc; // Set vtable at +0x20
  DAT_011298e8 = 0; // Global flag reset
  FUN_007edfb0(); // Sub-initialization call
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // Deallocation if flag bit 0 set
  }
  return this;
}