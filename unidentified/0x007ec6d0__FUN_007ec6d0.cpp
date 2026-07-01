// FUNC_NAME: SomeClass::releaseAndDelete
void __fastcall releaseAndDelete(undefined4 *this)
{
  if (this[1] != 0) {
    // Call virtual destructor or release method at vtable+0x4 on the object
    (**(code **)(*(int *)*this + 4))(this[1], 0);
    this[1] = 0;  // Clear pointer after release
  }
  // Call virtual destructor at vtable+0xC on this object
  (**(code **)(*(int *)*this + 0xc))();
  return;
}