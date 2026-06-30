// FUNC_NAME: EARSObject::~EARSObject
void __thiscall EARSObject::~EARSObject(EARSObject *this)
{
  // +0x00: vtable pointer (initial)
  // +0x04: pointer to subobject (likely a member or embedded object)
  *this = (EARSObject *)&PTR_FUN_00e36f1c; // set vtable to destructor-stage vtable
  if (this->field_0x04 != 0) {
    // Call virtual function at offset 0xc on the subobject (likely its destructor or cleanup)
    (*(void (__thiscall **)(void *))((int *)*this->field_0x04)[3])(); // offset 0xc = index 3
  }
  *this = (EARSObject *)&PTR_LAB_00e362b8; // set vtable to fully destructed vtable
  return;
}