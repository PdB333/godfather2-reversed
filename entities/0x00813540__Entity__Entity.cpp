// FUNC_NAME: Entity::Entity
// Function address: 0x00813540
// Constructor for Entity class (base class for game objects). Initializes vtable pointers and zeroes fields.

Entity * __thiscall Entity::Entity(Entity *this, int someParam)
{
  // Call base class constructor via FUN_0046c590
  baseClassConstructor(someParam);
  
  // Set vtable pointer at offset 0x00
  this->vtable = &PTR_FUN_00d73040;
  
  // Set secondary vtable pointer at offset 0x3C (0x0F * 4)
  this->secondaryVtable1 = &PTR_LAB_00d73030;
  
  // Set another vtable pointer at offset 0x48 (0x12 * 4)
  this->secondaryVtable2 = &PTR_LAB_00d7302c;
  
  // Zero out 16-bit fields
  this->field_0x54 = 0;   // offset 0x54 (param_1[0x15] as halfword)
  *(uint16_t *)((int)this + 0x56) = 0; // offset 0x56
  this->field_0x5C = 0;   // offset 0x5C (param_1[0x17] as halfword)
  *(uint16_t *)((int)this + 0x5E) = 0; // offset 0x5E
  
  // Initializing then overwriting a field - likely a bug or leftover constant
  this->magicField = 0xFE16702F; // offset 0x60 (param_1[0x18])
  this->field_0x50 = 0;   // offset 0x50 (param_1[0x14])
  this->field_0x58 = 0;   // offset 0x58 (param_1[0x16])
  this->magicField = 0;   // offset 0x60 overwritten to 0
  
  return this;
}