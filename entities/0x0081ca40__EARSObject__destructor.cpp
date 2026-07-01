// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(undefined4 *this)
{
  FUN_0081c980(); // call base/member destructor chain
  // Call virtual destructor hook: (vtable[1])(this+0x18, 0x2c)
  (**(code **)(*(int *)*this + 4))(this[6], 0x2c);
  this[6] = 0; // +0x18: clean up pointer
  return;
}