// FUNC_NAME: EARSObject::constructor
int __thiscall EARSObject::constructor(int this, byte flags)
{
  undefined4 **ppVtable;
  
  if (this == 0) {
    ppVtable = (undefined4 **)0x0;
  }
  else {
    ppVtable = (undefined4 **)(this + 0x20); // +0x20: vtable pointer offset
  }
  *ppVtable = &PTR_LAB_00d580f8; // Set initial vtable
  DAT_0112995c = 0; // Global flag reset
  FUN_007edfb0(); // Subsystem initialization call
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // Conditional destructor/free if flag bit 0 set
  }
  return this;
}