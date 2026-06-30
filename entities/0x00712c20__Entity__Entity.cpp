// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(Entity *this, byte allocFlag)
{
  // Initialize vtable pointer (likely EARS engine base class)
  this->vtable = (int *)&PTR_FUN_00d61a08; // VTable for Entity class

  // Call base class constructor (EARSObject or similar)
  EARSObject::EARSObject((EARSObject *)this);

  // If the object was allocated on the heap (allocFlag & 1), call deleting destructor
  if ((allocFlag & 1) != 0) {
    this->~Entity();         // Call destructor (including virtual destructor chain)
    operator delete(this);   // Free memory
  }

  return this;
}