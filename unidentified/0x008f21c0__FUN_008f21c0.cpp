// FUNC_NAME: SomeClass::releaseOrReset
void __fastcall SomeClass::releaseOrReset(int this)
{
  if (*(undefined4 **)(this + 0x2c) != (undefined4 *)0x0) {
    // Call virtual function at vtable[0] on the object at this+0x2c
    (**(code **)**(undefined4 **)(this + 0x2c))(0);
    // Call vtable[1] (likely destructor or dealloc) with size 0x3c
    (**(code **)(**(int **)(this + 0x28) + 4))(*(undefined4 *)(this + 0x2c),0x3c);
    *(undefined4 *)(this + 0x2c) = 0;
  }
  // Clear bits 9-10 (0x600) in flags at +0x10
  *(uint *)(this + 0x10) = *(uint *)(this + 0x10) & 0xfffff9ff;
  // Reset field at +0x204c to 0
  *(undefined4 *)(this + 0x204c) = 0;
  return;
}