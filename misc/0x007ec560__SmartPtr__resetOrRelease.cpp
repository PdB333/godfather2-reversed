// FUNC_NAME: SmartPtr::resetOrRelease
void __fastcall SmartPtr::resetOrRelease(undefined4 *this)

{
  // Check if the managed pointer is non-null
  if (this[1] != 0) {
    // Call the release function (vtable entry at +4) with the managed pointer and 0
    (**(code **)(*(int *)*this + 4))(this[1],0);
    // Set the managed pointer to null
    this[1] = 0;
  }
  // Call the destructor/uninit function (vtable entry at +0xc) on the smart pointer itself
  (**(code **)(*(int *)*this + 0xc))();
  return;
}