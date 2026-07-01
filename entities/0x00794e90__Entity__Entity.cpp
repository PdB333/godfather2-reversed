// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(Entity *this, int enableResource)
{
  uint resourceId;
  
  if (enableResource == 0) {
    resourceId = 0;
  }
  else {
    resourceId = FUN_00481610(); // getResourceId (returns some manager/ID)
  }
  FUN_0064d390(1,1); // general core initialization (e.g., setActive)
  this->vfptr = (undefined4 **)&PTR_LAB_00e317dc; // +0x00 set base vtable
  this->field_0x18 = 0; // +0x18
  FUN_00454a10(resourceId); // attachResource (associates resource/ID with object)
  this->field_0x24 = 1; // +0x24
  this->vfptr = (undefined4 **)&PTR_LAB_00d6a170; // +0x00 override to derived vtable
  this->field_0x34 = 0; // +0x34
  this->interfaceVfptr = (undefined4 **)&PTR_LAB_00d6a13c; // +0x28 set interface vtable
  this->someCallback = &LAB_00794050; // +0x30 function pointer (callback/trampoline)
  FUN_004a8ec0(0); // initializeSubComponent (e.g., animation, script, etc.)
  this->selfRef = &(this->interfaceVfptr); // +0x14 points to the interface vtable slot
  return this;
}