// FUNC_NAME: EARSComponent::~EARSComponent
void __fastcall EARSComponent::~EARSComponent(undefined4 *this)

{
  *this = &PTR_FUN_00d5ef34; // set vtable to custom destructor vtable
  this[2] = &PTR_LAB_00d5ef2c; // set secondary pointer (possibly another vtable or data)
  // Check if internal allocation exists at offset +0xE8 (this[0x3a])
  if (this[0x3a] != 0) {
    // Free the allocation at this+0xE8
    FUN_004daf90(this + 0x3a);
  }
  // Perform base cleanup (likely static or shared)
  FUN_006c9820();
  return;
}