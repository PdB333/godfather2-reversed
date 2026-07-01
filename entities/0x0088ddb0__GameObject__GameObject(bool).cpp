// FUNC_NAME: GameObject::GameObject(bool)
// Address: 0x0088ddb0
// Role: Constructor for a GameObject (or base class). Calls internal initialization, then optionally registers the object with a global manager if the flag is set.

undefined4 __thiscall GameObject::GameObject(GameObject* this, bool registerWithManager)
{
  // Call the internal initialization function (likely sets up base class members)
  this->initializeClass();

  // If the flag indicates the object should be registered (e.g., added to a global list or manager),
  // call the registration/destructor? The exact purpose of FUN_009c8eb0 is unclear,
  // but it is called with 'this' as argument. It might be a finalization step or a registration call.
  // Given the pattern, it could be a "registerWithManager" function.
  if ((registerWithManager & 1) != 0) {
    this->registerWithManager(); // FUN_009c8eb0
  }

  // Return the constructed object pointer (this)
  return (undefined4)this;
}