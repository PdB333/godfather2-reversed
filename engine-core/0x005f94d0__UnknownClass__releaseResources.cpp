// FUNC_NAME: UnknownClass::releaseResources
void FUN_005f94d0(void)

{
  undefined4 *this;
  
  if (this[3] != 0) {
    // Call vtable method at offset 4 to release resource at this[3]
    (**(code **)(*(int *)this[2] + 4))(this[3],0);
    this[3] = 0;
  }
  // Call vtable method at offset 0xC (likely destructor or release)
  (**(code **)(*(int *)this[2] + 0xc))();
  if (this[1] != 0) {
    // Call vtable method at offset 4 to release resource at this[1]
    (**(code **)(*(int *)*this + 4))(this[1],0);
    this[1] = 0;
  }
                    /* WARNING: Could not recover jumptable at 0x005f9516. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  // Call vtable method at offset 0xC (likely destructor or release)
  (**(code **)(*(int *)*this + 0xc))();
  return;
}