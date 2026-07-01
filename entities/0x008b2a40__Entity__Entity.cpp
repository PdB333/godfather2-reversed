// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(Entity *this)
{
  // +0x00: vtable pointer (main class vtable)
  *(BaseClassVTable **)this = &PTR_FUN_00d58a2c;
  // +0x3C: additional vtable pointer (interface or base class vtable)
  *(InterfaceVTable **)((char *)this + 0x3C) = &PTR_LAB_00d58a1c;
  // +0x48: another vtable pointer (secondary interface)
  *(InterfaceVTable **)((char *)this + 0x48) = &PTR_LAB_00d58a18;
  // +0x6C: initialize sub-object (e.g., a member or secondary base)
  FUN_00408310(this + 0x1B);  // member at offset 0x6C
  // Run a global/static initialization (possibly register class in factory)
  FUN_008b2820();
  return;
}