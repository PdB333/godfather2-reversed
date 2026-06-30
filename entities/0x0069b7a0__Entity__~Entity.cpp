// FUNC_NAME: Entity::~Entity
undefined4 * __thiscall Entity::destructor(Entity *this, byte deleteFlag)
{
  // +0x2c: pointer to callback data (e.g., script or behavior instance)
  // +0x38: function pointer to cleanup/release callback
  if (this->m_pCallbackData != 0) {
    (*(code *)this->m_pCallbackFunc)(this->m_pCallbackData);
  }
  // Set vtable to base class (Entity) vtable
  this->vtable = (EntityVTable *)&PTR_FUN_00d5ce9c;
  // +0x14: pointer to a sub-object that needs destruction (e.g., a behavior or child entity)
  FUN_0069a0e0(this->m_pChildObject);
  if ((deleteFlag & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  return this;
}