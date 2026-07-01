// FUNC_NAME: Entity::Entity
// Constructor for an Entity object, likely part of the EARS engine's entity hierarchy.
// Sets up vtable pointers for multiple inheritance and initializes member fields.
// Params: this – pointer to object being constructed, createFlag – if non-zero, allocates a sub-object via FUN_00481610.
// Callees: FUN_00481610 (subObjectAllocator), FUN_0064d390 (debug/init), FUN_00454a10 (baseEntityInit)
// Vtable labels: PTR_LAB_00e317dc (temporary base vtable), PTR_LAB_00d6a8d8 (main derived vtable), PTR_LAB_00d6a724 (secondary base vtable)
Entity * __thiscall Entity::Entity(Entity *this, int createFlag)
{
  undefined4 subObject;
  
  // Allocate a sub-object only if createFlag is non-zero
  if (createFlag == 0) {
    subObject = 0;
  }
  else {
    subObject = entityAllocSubObject(); // FUN_00481610
  }
  
  // General initialization call (maybe sets memory guard bytes or debug flags)
  debugInit(1, 1); // FUN_0064d390
  
  // Set temporary vtable (base class before construction)
  this->vtableBase = &gBaseEntityVTable; // PTR_LAB_00e317dc
  // Clear a field at offset 0x18
  this->field_0x18 = 0; // param_1[6]
  
  // Initialize the base entity sub-object (may set base vtable internally)
  baseEntityInit(subObject); // FUN_00454a10
  
  // Set flag that entity is active/initialized
  this->activeFlag = 1; // param_1[9] at offset 0x24
  
  // Override main vtable to derived class vtable
  this->vtableMain = &gDerivedEntityVTable; // PTR_LAB_00d6a8d8
  // Set secondary vtable (for second base in multiple inheritance)
  this->vtableSecondary = &gSecondaryBaseVTable; // param_1[10] at offset 0x28 = &PTR_LAB_00d6a724
  
  // Set a function pointer (probably a callback, e.g., update routine)
  this->updateHandler = &gEntityUpdateFunction; // param_1[0xc] at offset 0x30 = &LAB_0079b150
  // Clear several fields
  this->field_0x34 = 0;  // param_1[0xd]
  this->field_0x44 = 0;  // param_1[0x11]
  this->field_0x54 = 0;  // param_1[0x15]
  this->field_0x64 = 0;  // param_1[0x19]
  // Initialize a field with a global value (e.g., current game time)
  this->globalTimeStamp = g_dat_00d5780c; // param_1[0x1d] at offset 0x74
  
  // Set a self-referential pointer: points to the secondary base sub-object (offset 0x28)
  this->selfPtrToSub = reinterpret_cast<EntityBase *>(&this->vtableSecondary); // param_1[5] at offset 0x14 = this + 0x28
  
  return this;
}