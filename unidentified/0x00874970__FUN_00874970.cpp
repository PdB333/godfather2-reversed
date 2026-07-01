// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  if (this[3] != 0) {
    FUN_004daf90(this + 3); // likely operator delete or free
  }
  this[1] = &PTR_FUN_00e32808; // vtable pointer for base class
  puVar2 = (undefined4 *)this[2]; // linked list head at +0x08
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar2[1]; // next pointer at +0x04
    puVar2[1] = 0; // clear next
    *puVar2 = 0; // clear data
    puVar2 = puVar1;
  }
  *this = &PTR_LAB_00e2f0c0; // vtable pointer for this class
  return;
}