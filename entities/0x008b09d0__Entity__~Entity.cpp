// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity(Entity *this)
{
  // Set vtable to derived class vtable (for destruction)
  *(int **)this = &vtable_00d7a648;
  // Call base class destructor
  Base::~Base();
  // Delete child objects if present
  if (this->field_0x28 != 0) {
    FUN_009c8f10(this->field_0x28);  // Release child object at +0x28
  }
  if (this->field_0x1c != 0) {
    FUN_009c8f10(this->field_0x1c);  // Release child object at +0x1C
  }
  if (this->field_0x10 != 0) {
    FUN_009c8f10(this->field_0x10);  // Release child object at +0x10
  }
  if (this->field_0x04 != 0) {
    FUN_009c8f10(this->field_0x04);  // Release child object at +0x04
  }
  // Restore vtable to base class vtable (to prevent double deletion)
  *(int **)this = &vtable_00d7a644;
  // Reset global flag indicating this object exists
  g_someGlobalFlag = 0;
}