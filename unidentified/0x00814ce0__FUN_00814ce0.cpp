// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  int iVar1;
  
  iVar1 = this[0x1e]; // +0x78: some pointer member
  *this = &PTR_FUN_00d730f4; // vtable pointer
  this[1] = &PTR_LAB_00d730f0; // vtable pointer for base class?
  if (iVar1 != 0) {
    FUN_00816660(); // likely release/deallocate
    FUN_009c8eb0(iVar1); // likely free/delete
    this[0x1e] = 0; // +0x78: clear pointer
  }
  iVar1 = this[0x1f]; // +0x7C: another pointer member
  if (iVar1 != 0) {
    FUN_00816660(); // likely release/deallocate
    FUN_009c8eb0(iVar1); // likely free/delete
    this[0x1f] = 0; // +0x7C: clear pointer
  }
  this[1] = &PTR_LAB_00d730ec; // vtable pointer for base class after destruction?
  DAT_011298d0 = 0; // global flag
  return;
}