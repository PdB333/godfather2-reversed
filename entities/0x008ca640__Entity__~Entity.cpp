// FUNC_NAME: Entity::~Entity
undefined4 * __thiscall Entity::~Entity(Entity *this, byte deallocFlag)
{
  // Switch vtable to base class for proper virtual destruction order
  this->vtable = &VTable_BaseEntity;
  
  // Release any allocated resource at offset +0x0C
  if (this->m_pSomeResource != 0) {
    this->releaseResource(); // FUN_009f01a0 - likely cleanup helper
  }
  
  // Set final vtable (often to a sentinel or base base class)
  this->vtable = &VTable_Base_Again;
  
  // Deallocate memory if the flag indicates ownership
  if ((deallocFlag & 1) != 0) {
    operator delete(this); // FUN_009c8eb0 - heap deallocation
  }
  
  return (undefined4 *)this;
}