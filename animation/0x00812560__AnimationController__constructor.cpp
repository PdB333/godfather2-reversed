// FUNC_NAME: AnimationController::constructor
void __fastcall AnimationController::constructor(AnimationController *this)
{
  // vtable assignment (likely AnimationController vtable)
  *(undefined4 *)this = &PTR_FUN_00d72fc0;
  // Initialize offset +0x3C (0xF * 4) - possibly a next pointer or callback
  *(undefined4 *)((char *)this + 0x3c) = &PTR_LAB_00d72fb0;
  // Initialize offset +0x48 (0x12 * 4) - another state pointer
  *(undefined4 *)((char *)this + 0x48) = &PTR_LAB_00d72fac;

  // Check flags at +0x50 (0x14 * 4)
  if ((*(byte *)((char *)this + 0x50) & 1) == 0) {
    // If bit 0 not set, call some initialization function
    FUN_00812200();
  }

  // Check another flag bit at +0x50
  if ((*(byte *)((char *)this + 0x50) & 2) != 0) {
    // If bit 1 is set, call function with parameters: size 0x30, pointer to offset +0x3C
    FUN_00403720(0x30, (int *)((char *)this + 0x3c));
  }

  // Post-construction call (possibly register with manager)
  FUN_0046c640();
}