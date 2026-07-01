// FUNC_NAME: Entity::release
void Entity::release(Entity* thisPtr)
{
  // Check if the entity pointer is valid and has a non-null reference count or handle at +0x08
  if ((thisPtr != 0) && (*(int*)(thisPtr + 8) != 0)) {
    // Call the internal release/decrement function (likely decrements ref count or frees resources)
    Entity::internalRelease(thisPtr);
  }
  return;
}