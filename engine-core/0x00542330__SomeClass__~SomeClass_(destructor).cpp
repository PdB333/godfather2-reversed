// FUNC_NAME: SomeClass::~SomeClass (destructor)
void __thiscall SomeClass::~SomeClass(void *this) {
  undefined4 *vtable2;
  undefined4 *ptr;

  ptr = (undefined4 *)this + 2;
  *(undefined4 *)this = &PTR_LAB_00e3926c;    // Set vtable slot at +0x00
  *(undefined4 *)((int)this + 4) = &PTR_LAB_00e39280; // Set vtable slot at +0x04
  *ptr = &PTR_LAB_00e39294;                    // Set vtable slot at +0x08
  if (*(int *)((int)this + 0x10) != 0) {       // Check if +0x10 is non-null
    FUN_009f1b20(this);                        // Release first sub-object
    FUN_009f1ad0(ptr);                         // Release second sub-object
    FUN_009f01a0();                            // Final cleanup
    *(int *)((int)this + 0x10) = 0;            // Clear +0x10 to 0
  }
  *ptr = &PTR_LAB_00e39260;                    // Restore vtable slot at +0x08 to base class
  *(undefined4 *)((int)this + 4) = &PTR_LAB_00dc3dd4; // Restore vtable slot at +0x04 to base
  *(undefined4 *)this = &PTR___purecall_00e3924c; // Set +0x00 to purecall (destroyed state)
  return;
}