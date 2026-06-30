// FUNC_NAME: SomeComponent::~SomeComponent
undefined4 * __thiscall SomeComponent::~SomeComponent(undefined4 *this, byte param_2)
{
  // Destructor: releases two sub-objects at offsets +0x08 and +0x10 if non-null,
  // restores vtable to base class (PTR_LAB_00e3729c), then deletes self if param_2 & 1.
  if (this[4] != 0) {
    // Release sub-object at +0x10 (likely a pointer to a contained object)
    FUN_004daf90(this + 4);
  }
  if (this[2] != 0) {
    // Release sub-object at +0x08
    FUN_004daf90(this + 2);
  }
  // Set vtable to base class vtable (for proper deletion in base-to-derived order)
  *this = (undefined4 *)&PTR_LAB_00e3729c;
  if ((param_2 & 1) != 0) {
    // If flag indicates deletion, call operator delete
    FUN_004eb3d0(this);
  }
  return this;
}