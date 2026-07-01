// FUNC_NAME: Entity::constructor
// Function address: 0x008c82f0
// Role: Constructor for Entity class, initializes fields including a vtable pointer, flags, parent/ID, and default values from a global.

undefined4 * __thiscall Entity::constructor(Entity *this, uint32_t param2, uint32_t param3)
{
  uint32_t defaultVal;
  
  // Offset +0x0C: Store third parameter (likely parent pointer or ID)
  this->field_0x0C = param3;
  // Offset +0x14: clear field
  this->field_0x14 = 0;
  // Load global default value (e.g., initial health, position, etc.)
  defaultVal = _DAT_00d5780c;
  // Set vtable pointer (offset +0x00)
  this->vtable = &PTR_LAB_00d7bebc;
  // Offset +0x04: set to 1 (likely active/enabled flag)
  this->field_0x04 = 1;
  // Offset +0x08: store second parameter (e.g., ID or type)
  this->field_0x08 = param2;
  // Offset +0x10: clear field
  this->field_0x10 = 0;
  // Offset +0x18: clear field
  this->field_0x18 = 0;
  // Offset +0x1C: clear field
  this->field_0x1C = 0;
  // Offset +0x20: set from default value
  this->field_0x20 = defaultVal;
  // Offset +0x24: set from default value
  this->field_0x24 = defaultVal;
  // Offset +0x28: set from default value
  this->field_0x28 = defaultVal;
  // Call base class initializer (FUN_00791e70)
  Entity_InitializeBase(this);
  return this;
}