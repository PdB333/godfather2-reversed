// FUNC_NAME: Entity::Entity
// Function address: 0x005c16e0
// Role: Constructor for Entity class (base class with multiple inheritance)
// Sets up vtables, calls base constructors, initializes fields

void __thiscall Entity::Entity(Entity *this)
{
  // Set vtable pointers for base classes
  // +0x00: primary vtable (Object)
  this->vtable0 = &PTR_FUN_00e3e7f8;
  // +0x04: secondary vtable (SimObject)
  this->vtable4 = &PTR_LAB_00e3e85c;

  // Call base constructors
  Object::Object();      // FUN_005c1990
  SimObject::SimObject(); // FUN_005c0a90

  // Update secondary vtable to intermediate derived vtable
  this->vtable4 = &PTR_FUN_00e3e78c;

  // Call additional initialization (possibly Entity-specific base)
  Entity::initBase();    // FUN_005c0360

  // Initialize member fields
  // +0x18: some flag/counter
  this->field_18 = 0;
  // +0x1C: another flag/counter
  this->field_1C = 0;

  // Release any previously held reference at +0x14
  if (this->m_pSomePointer != 0) {
    // Call virtual function on global manager (DAT_012234ec) to release
    // (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(this->m_pSomePointer, 0);
    g_pManager->releaseReference(this->m_pSomePointer, 0);
  }
  this->m_pSomePointer = 0;

  // Set final vtable for complete object
  this->vtable4 = &PTR_LAB_00e3e74c;
}