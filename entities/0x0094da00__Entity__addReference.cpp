// FUNC_NAME: Entity::addReference
void __fastcall Entity::addReference(int this)
{
  if (*(int *)(this + 0x94) == 0) {
    // First reference - need to initialize/activate the entity
    Entity::activate(this);
  }
  // Increment reference count
  *(int *)(this + 0x94) = *(int *)(this + 0x94) + 1;
}