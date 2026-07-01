// FUNC_NAME: Entity::Entity (constructor)
// Address: 0x00908c20
// Role: Constructor for an Entity object with multiple inheritance (vtables at +0x00, +0x3C, +0x48) and a sub-object at +0x18.
// The constructor initializes the vtable pointers, calls sub-object constructors, performs global initialization,
// and optionally registers the object with a manager (if param_2 & 1).

undefined4 * __thiscall Entity::Entity(Entity *this, byte allocFlag)
{
  // Set vtable pointers for multiple inheritance
  this->vtable1 = &PTR_FUN_00d8314c;          // +0x00: primary vtable
  this->vtable2 = &PTR_LAB_00d8313c;          // +0x3C: secondary vtable
  this->vtable3 = &PTR_LAB_00d83138;          // +0x48: tertiary vtable

  // Initialize sub-object at offset 0x18 (likely a base class or embedded component)
  Entity::initSubObject1(&this->subObject);   // +0x18: calls FUN_004086d0
  Entity::initSubObject2(&this->subObject);   // +0x18: calls FUN_00408310

  // Global initialization (e.g., singleton manager setup)
  initializeGlobalState();                    // FUN_0046c640

  // If the object was allocated with new (allocFlag & 1), register it with the manager
  if ((allocFlag & 1) != 0) {
    registerWithManager(this, sizeof(Entity)); // FUN_0043b960(this, 0x68)
  }

  return this;
}