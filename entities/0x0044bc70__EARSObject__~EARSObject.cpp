// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::destroy(EARSObject* this)
{
  // Set vtable to first destructor vtable
  this->vtable = &PTR_FUN_00e31440;                 // +0x00: vtable pointer
  this->field_10 = &PTR_LAB_00e314c8;               // +0x10: another vtable-like pointer

  // Destroy sub-object at +0x14 if non-null
  if (this->field_14 != nullptr) {
    (*(void (__thiscall**)(void*))(*this->field_14))(1); // Call first virtual destructor
  }

  // Update vtable to a different subobject's vtable
  this->field_10 = &PTR_LAB_00e31528;               // +0x10: updated vtable
  this->vtable = &PTR_FUN_00e353e0;                 // +0x00: updated vtable

  // Destroy or cleanup sub-object at +0x0C if non-zero
  if (this->field_0C != 0) {
    FUN_004a6400();                                  // internal cleanup function
  }

  // Destroy sub-object at +0x0C if non-null
  if (this->field_0C != nullptr) {
    (*(void (__thiscall**)(void*))(*this->field_0C))(1); // Call first virtual destructor
  }

  // Final base vtable restoration
  this->vtable = &PTR_LAB_00e2f638;                 // +0x00: base class vtable
}