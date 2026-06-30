// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(Entity *this, undefined4 param_2, undefined4 param_3)

{
  // Call base class constructor (Object or similar)
  Object::Object(param_2, param_3);
  
  // Initialize fields specific to Entity
  this->field_0xF4 = DAT_00d5f6f0;           // +0xF4 (global singleton or static pointer)
  this->vtable = &Entity_vtable;             // +0x00 (primary vtable)
  this->interface_vtable = &Entity_interface_vtable; // +0x50 (+0x14*4, secondary vtable for interface)
  this->field_0x108 = 0;                     // +0x108
  this->field_0x120 = 0;                     // +0x120
  *(undefined1 *)(this + 0x3e) = 0;          // +0xF8 (byte field)
  this->field_0x10C = 0;                     // +0x10C
  *(undefined1 *)(this + 0x47) = 0;          // +0x11C (byte field)
  this->field_0x104 = 0;                     // +0x104
  this->field_0x100 = 0;                     // +0x100
  this->field_0xFC = 0;                      // +0xFC
  this->field_0x118 = 0;                     // +0x118
  this->field_0x114 = 0;                     // +0x114
  this->field_0x110 = 0;                     // +0x110
  this->field_0xA8 = this->field_0xA8 | 0x2020; // +0xA8 (set flags)
  return this;
}