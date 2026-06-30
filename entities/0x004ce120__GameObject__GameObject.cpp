// FUNC_NAME: GameObject::GameObject
GameObject* __thiscall GameObject::GameObject(GameObject* this, byte allocFlags)
{
  // Set vtable pointer to GameObject's vtable
  *this = &GameObject_vtable;

  // Call base class constructor or initialization
  GameObject::constructBase();

  // Initialize member variables
  GameObject::initMembers();

  // Perform additional setup
  GameObject::finalizeInit();

  // If the object was dynamically allocated (bit 0 set), call deallocation
  if ((allocFlags & 1) != 0) {
    operator delete(this);
  }

  return this;
}