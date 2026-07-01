// FUNC_NAME: GameApplication::GameApplication (speculative - constructor)

void __thiscall GameApplication::GameApplication(GameApplication *this)
{
  // Set up vtable pointers for multiple inheritance:
  // Primary vtable at offset 0
  *this = (GameApplication *)&PTR_FUN_00d87980;
  // Secondary base class vtable at offset 4
  this->base2 = (Base2Class *)&PTR_LAB_00d87958;
  // Additional vtable at offset 0x4C (likely third base)
  *(void **)((uint8_t *)this + 0x4C) = &PTR_LAB_00d87948;
  // Fourth vtable at offset 0x58 (set to initial value)
  *(void **)((uint8_t *)this + 0x58) = &PTR_LAB_00d87944;

  // Call base class constructor (likely for one of the bases)
  FUN_00927b50(this);

  // After base constructor, set the fourth vtable to a different one (override)
  *(void **)((uint8_t *)this + 0x58) = &PTR_LAB_00d87940;

  // Initialize global flag
  DAT_01129a74 = 0;

  // Additional initialization calls
  FUN_004083d0();
  FUN_005c16e0();
}