// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Call base destructor or cleanup function
  FUN_007ecdd0();
  
  // Call virtual function at vtable+4 (likely release/delete) on member at +0x18 (param_1[6])
  (**(code **)(*(int *)*this + 4))(this[6], 0x24);
  
  // Null out the member pointer
  this[6] = 0;
  
  // Call another cleanup function
  FUN_007ed520();
}