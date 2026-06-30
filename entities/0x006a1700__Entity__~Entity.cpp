// FUNC_NAME: Entity::~Entity
undefined4 * __thiscall Entity::~Entity(Entity *this, byte freeMemoryFlag)
{
  // Offset +0x00: vtable pointer (set to base class vtable during destruction)
  // Offset +0x04: pointer to owned sub-object (sub-object of type unknown)
  // Offset +0x18: pointer to another owned sub-object

  // Set vtable to base class vtable to ensure proper virtual dispatch during destruction
  *(void ***)this = &PTR_LAB_00d5d090;

  // Decrement global instance counter (if any)
  s_entityCount = 0;

  // Call base class (or other) cleanup routine
  baseClassCleanup();

  // Destroy sub-object at +0x18
  deallocate(this->m_pSubObjectAt18);

  // Check and destroy sub-object pointed to by +0x04
  void *subObj = this->m_pSubObjectAt04;
  if (subObj != 0) {
    // Destroy member at offset +0x30 within sub-object
    deallocate(*(void **)((char *)subObj + 0x30));
    // Destroy the sub-object itself
    operatorDelete(subObj);
  }

  // If caller requested memory deallocation, free this instance
  if (freeMemoryFlag & 1) {
    operatorDelete(this);
  }

  return (undefined4 *)this;
}