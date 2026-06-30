// FUNC_NAME: CleanupObject::~CleanupObject
void __fastcall CleanupObject::~CleanupObject(CleanupObject *this)
{
  // Set vtable to derived class vtable (PTR_FUN_00d5cec4)
  this->vtable = &PTR_FUN_00d5cec4;

  // Clean up first sub-object: if non-null, call its destructor function stored at +0x48 (0x12*4)
  if (this->subObject1 != 0) {
    ((void (*)(void *))this->subObject1Destructor)(this->subObject1);
  }

  // Clean up second sub-object: if non-null, call its destructor function stored at +0x38 (0xe*4)
  if (this->subObject2 != 0) {
    ((void (*)(void *))this->subObject2Destructor)(this->subObject2);
  }

  // Set vtable to base class vtable (PTR_FUN_00d5ce9c) and call base destructor
  this->vtable = &PTR_FUN_00d5ce9c;
  FUN_0069a0e0(this->field_0x14); // +0x14 (5*4) – likely base class member or this pointer
}