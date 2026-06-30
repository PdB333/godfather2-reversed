// FUNC_NAME: GameObject::GameObject
undefined4 * __thiscall GameObject::GameObject(GameObject *this, byte isHeapAllocated)
{
  // Set vtable pointer for main class
  this->vtable = &PTR_FUN_00d5f42c; // +0x00: main vtable
  // Set vtable pointers for base classes (multiple inheritance)
  this->baseVtable1 = &PTR_LAB_00d5f41c; // +0x3C (offset 0xf * 4)
  this->baseVtable2 = &PTR_LAB_00d5f418; // +0x48 (offset 0x12 * 4)
  // Initialize subobject at offset 0x50 (param_1 + 0x14)
  // First call: likely constructor for a member (e.g., a string or list)
  FUN_004086d0(&this->subObject); // +0x50
  // Second call: likely initialization or copy constructor
  FUN_00408310(&this->subObject); // +0x50
  // Global initialization (e.g., singleton or static)
  FUN_0046c640();
  // If the object was heap-allocated, call a cleanup/registration function
  if ((isHeapAllocated & 1) != 0) {
    FUN_0043b960(this, 0x6c); // size 0x6c = 108 bytes (total object size)
  }
  return this;
}