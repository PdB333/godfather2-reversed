// FUNC_NAME: Entity::Entity
undefined4 * Entity::Entity(Entity *this)

{
  // Call base class constructor (likely BaseEntity or EARS::Object)
  BaseEntity::BaseEntity((BaseEntity *)this);

  // Set virtual table pointers for multiple inheritance or interfaces
  // +0x2E0: Initial purecall vtable (overridden below)
  this->vtable_2E0 = &g_purecall_vtable;
  // +0x2E4: Another interface vtable
  this->vtable_2E4 = &g_interface_vtable_00dc3dd4;

  // Zero out fields at +0x2E8 (offset 0xBA) through +0x2FC (0xBF?) but only 0xBA set to 0
  this->field_2E8 = 0;

  // Primary vtable pointer at +0x00
  this->vtable = &g_entity_vtable_00e39808;

  // Interface vtable at +0x3C, +0x48, +0x50, +0x54, +0x58
  this->interface1 = &g_interface1_vtable_00e39a64;   // +0x3C
  this->interface2 = &g_interface2_vtable_00e39a74;   // +0x48
  this->interface3 = &g_interface3_vtable_00e39a78;   // +0x50
  this->interface4 = &g_interface4_vtable_00e39a80;   // +0x54
  this->interface5 = &g_interface5_vtable_00e39ae0;   // +0x58

  // Override the previously set vtable pointers at +0x2E0 and +0x2E4
  this->vtable_2E0 = &g_entity_specific_vtable_00e39b44;  // +0x2E0
  this->vtable_2E4 = &g_entity_specific_vtable_00e39b58;  // +0x2E4

  // Initialize many fields to zero (offsets 0xCE to 0xE3)
  // +0x338 through +0x38C
  this->field_338 = 0;
  this->field_33C = 0;
  this->field_340 = 0;
  this->field_344 = 0;
  this->field_348 = 0;
  this->field_34C = 0;
  this->field_330 = 0;   // +0xCC (0x330) (note: order is slightly out of sequence)
  this->field_334 = 0;   // +0xCD (0x334)
  this->field_350 = 0;   // +0xD4 (0x350)
  this->field_354 = 0;   // +0xD5 (0x354)
  this->field_358 = 0;   // +0xD6 (0x358)
  this->field_360 = 0;   // +0xD8 (0x360)
  this->field_364 = 0;   // +0xD9 (0x364)
  this->field_368 = 0;   // +0xDA (0x368)
  this->field_374 = 0;   // +0xDD (0x374)
  this->field_378 = 0;   // +0xDE (0x378)
  this->field_37C = 0;   // +0xDF (0x37C)
  this->field_380 = 0;   // +0xE0 (0x380)
  this->field_384 = 0;   // +0xE1 (0x384)
  this->field_388 = 0;   // +0xE2 (0x388)
  this->field_38C = 0;   // +0xE3 (0x38C)

  // Set two flags to 1 (offsets 0xE4 and 0xE5 = +0x390 and +0x394)
  this->flagActive = 1;      // +0x390
  this->flagEnabled = 1;     // +0x394

  return this;
}