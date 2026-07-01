// FUNC_NAME: EntityHandle::EntityHandle
// Function address: 0x0077a910
// Role: Constructor for EntityHandle class. Initializes vtable, stores a reference to a manager/owner, and retrieves a handle via a call to a manager method.

EntityHandle * __thiscall EntityHandle::EntityHandle(EntityHandle *this, ManagerType *owner)
{
  this->vtable = (EntityHandleVTable *)&PTR_LAB_00d684d0; // Set vtable pointer
  this->owner = owner; // +0x04: Store owner/manager pointer
  this->handle = 0; // +0x08: Initialize handle to null
  this->handle = owner->getSomeHandle(); // Retrieve handle from owner
  return this;
}