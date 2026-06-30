// FUNC_NAME: GameObject::GameObject
undefined4 __thiscall GameObject::GameObject(undefined4 this, byte initFlag)
{
  // Call base class constructor or internal initializer
  GameObject::initBase();

  // If bit 0 of initFlag is set, call additional initialization
  if ((initFlag & 1) != 0) {
    // Likely constructs sub-objects or performs deferred setup
    GameObject::constructSubObjects(this);
  }

  return this;
}