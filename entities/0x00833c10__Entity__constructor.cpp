// FUNC_NAME: Entity::constructor

undefined4 __thiscall Entity::constructor(Entity *this, byte constructionFlags)
{
  // Call base class constructor/initializer
  Entity::baseInit(this);
  
  // If the lower bit of constructionFlags is set, allocate additional memory (size 0xE4 bytes)
  // This is likely for a sub-object or dynamic allocation tied to this entity
  if ((constructionFlags & 1) != 0) {
    // FUN_0043b960 may be a memory manager function: reserves or registers 0xE4 bytes
    // Typical size for an Entity's internal data (e.g., properties, component list)
    Entity::allocateSubData(this, 0xE4);
  }
  
  // Return 'this' pointer; standard for constructor
  return this;
}