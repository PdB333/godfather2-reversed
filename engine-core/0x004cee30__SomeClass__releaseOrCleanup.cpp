// FUNC_NAME: SomeClass::releaseOrCleanup
void FUN_004cee30(void)
{
  undefined4 *this; // unaff_ESI assumes this is __thiscall with 'this' in ESI
  
  // +0x0C: member3 (offset 12) - check if non-null
  if (this[3] != 0) {
    // Call release/delete on member3 via vtable at this[2] (offset 8) +4
    (**(code **)(*(int *)this[2] + 4))(this[3], 0);
    this[3] = 0;
  }
  
  // Call some cleanup via vtable at this[2] (offset 8) +0xC
  (**(code **)(*(int *)this[2] + 0xc))();
  
  // +0x04: member1 (offset 4) - check if non-null
  if (this[1] != 0) {
    // Call release/delete on member1 via vtable at this[0] (offset 0) +4
    (**(code **)(*(int *)*this + 4))(this[1], 0);
    this[1] = 0;
  }
  
  // Call some cleanup via vtable at this[0] (offset 0) +0xC
  (**(code **)(*(int *)*this + 0xc))();
  
  return;
}