// FUNC_NAME: Entity::Entity
undefined4 __thiscall Entity::Entity(int this, byte param_2)
{
  // Call base class constructor at 0x007dd2f0 (likely BaseObject or similar)
  BaseObject::BaseObject(this);

  // If bit0 of param_2 is set, perform additional initialization (e.g., vtable setup)
  if ((param_2 & 1) != 0) {
    DerivedClass::vtableInit(this);
  }

  return this;
}