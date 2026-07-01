// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(Entity *this, byte initFlags)
{
  // Set vtable at offset 0x0
  *this = (undefined4 *)&ENTITY_VTABLE;
  // Set secondary vtable at +0x3C
  this->vtbl2 = (undefined4 *)&ENTITY_VTBL2;
  // Set tertiary vtable at +0x48
  this->vtbl3 = (undefined4 *)&ENTITY_VTBL3;
  // Set another vtable at +0x158 (redundant? likely only one assignment intended)
  this->vtbl4 = (undefined4 *)&ENTITY_VTBL4;
  this->vtbl4 = (undefined4 *)&ENTITY_VTBL4_ALT; // Possibly a bug in decompilation, original likely set two different offsets

  // Clear global flag
  g_entityInitFlag = 0;

  // Call subclass or helper initialization
  EntitySubsystemInit();

  // If the low bit is set, allocate memory for this (placement new / operator new?)
  if ((initFlags & 1) != 0) {
    CustomAlloc(this, 0x15c);
  }

  return this;
}