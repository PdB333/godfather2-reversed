// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(undefined4 *this, byte flag)
{
  // Set vtable pointer (class-specific vtable)
  *this = &PTR_FUN_00d814a4;
  // Set secondary vtable pointers at offsets +0x3C and +0x48 (0xF*4, 0x12*4)
  this[0xf] = &PTR_LAB_00d81494;
  this[0x12] = &PTR_LAB_00d81490;
  // Initialize sub-object at offset +0x68 (0x1A*4) - likely a base class or member
  FUN_004086d0(this + 0x1a);
  FUN_00408310(this + 0x1a);
  // Global initialization (e.g., memory manager, static data)
  FUN_0046c640();
  // If flag's low bit is set, free the object's memory (size 0x70 = 112 bytes)
  if ((flag & 1) != 0) {
    FUN_0043b960(this, 0x70);
  }
  return this;
}