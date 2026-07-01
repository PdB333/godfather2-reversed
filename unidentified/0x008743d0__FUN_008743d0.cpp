// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d76304; // vtable pointer assignment
  FUN_00873bb0(0); // base class constructor call with 0 argument
  *(undefined1 *)((int)this + 5) = 0; // initialize byte at offset +5 to 0
  return;
}