// FUNC_NAME: SomeClass::releaseAndDelete
void __fastcall SomeClass::releaseAndDelete(undefined4 *this)
{
  // Check if there's a child object at offset +0x04
  if (this[1] != 0) {
    // Call virtual function at vtable+0x04 (likely release/decRef) on the child object
    (**(code **)(*(int *)*this + 4))(this[1], 0);
    // Clear the child pointer
    this[1] = 0;
  }
  
  // Call virtual function at vtable+0x0C (likely destructor/delete)
  (**(code **)(*(int *)*this + 0xc))();
  return;
}