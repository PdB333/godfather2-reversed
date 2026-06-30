// FUNC_NAME: Sentient::Sentient
// Function address: 0x006c9760
// Role: Constructor for Sentient base class (EARS engine entity base)
// Initializes vtable(s), sets default fields (health states, target ID, etc.)
undefined4 * __thiscall Sentient::Sentient(Sentient *this, void *initializer, void *extraArg)
{
  // Call base constructor (likely SimBase or Entity)
  FUN_00473950(initializer);

  // Set first vtable pointer (primary class)
  this->vtable0 = &PTR_FUN_00d5f060;
  // Set second vtable pointer at offset +0x08 (multiple inheritance, e.g. NetReflectable)
  *(void **)((int)this + 8) = &PTR_LAB_00d5f058;

  // Zero out state fields from +0x64 to +0xAC (approx)
  this->field_0x64 = 0;            // +0x64
  this->field_0x68 = 0;            // +0x68
  this->someInvalidID = 0xFFFFFFFF; // +0x6c: sentinel value (invalid target/object handle)
  this->field_0x70 = 0;            // +0x70
  this->field_0x74 = 0;            // +0x74
  this->field_0x78 = 0;            // +0x78
  *(int *)((int)this + 0x7c) = 0;  // +0x7c (byte write? assumed int)
  this->field_0x80 = 0;            // +0x80
  this->field_0x84 = 0;            // +0x84
  this->field_0x88 = 0;            // +0x88
  this->field_0x8c = 0;            // +0x8c
  this->field_0x90 = 0;            // +0x90
  this->field_0x94 = 0;            // +0x94
  this->field_0x98 = 0;            // +0x98
  this->field_0x9c = 0;            // +0x9c
  this->field_0xa0 = 0;            // +0xa0
  this->field_0xa4 = 0;            // +0xa4
  this->field_0xa8 = 0;            // +0xa8
  this->field_0xac = 0;            // +0xac

  // Call secondary initialization function
  FUN_006c9660(initializer, extraArg);

  return this;
}