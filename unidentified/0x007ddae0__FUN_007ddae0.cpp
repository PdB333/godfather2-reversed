// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  int *piVar1;
  int iVar2;
  
  *this = &PTR_LAB_00d6f57c; // vtable pointer, likely base class
  if (((uint)((int *)this[0x16])[0x238] >> 10 & 1) != 0) {
    (**(code **)(*(int *)this[0x16] + 0x260))(); // call virtual function at vtable+0x260
  }
  piVar1 = this + 0x1d; // +0x74 offset (0x1d * 4)
  if ((this[0x1d] != 0) && (this[0x1d] != 0x48)) {
    if (*piVar1 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1 + -0x48;
    }
    if (*(char *)(iVar2 + 0x161) != '\0') {
      FUN_00701440(); // likely some cleanup function
    }
  }
  FUN_007f6420(0x26); // release resource type 0x26
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1); // delete/free pointer at +0x74
  }
  *this = &PTR_LAB_00d6b95c; // vtable pointer, likely derived class
  FUN_0080ea60(); // base class destructor call
  return;
}