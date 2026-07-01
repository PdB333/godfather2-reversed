// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(SomeClass* this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d79b38;
  
  // Set additional function pointers at known offsets
  this->field_0x3C = &PTR_LAB_00d79b28;  // +0x3C
  this->field_0x48 = &PTR_LAB_00d79b24;  // +0x48
  
  // If global flag is set, call additional cleanup
  if (DAT_0112b9b4 != 0) {
    FUN_008b0eb0(this);
  }
  
  // Call destructors for sub-objects if they exist
  // Each sub-object has a vtable pointer and a destructor function pointer
  if (this->field_0x88 != 0) {  // +0x88
    ((void (*)(void*))this->field_0x94)(this->field_0x88);  // +0x94 is destructor function pointer
  }
  if (this->field_0x78 != 0) {  // +0x78
    ((void (*)(void*))this->field_0x84)(this->field_0x78);  // +0x84 is destructor function pointer
  }
  if (this->field_0x60 != 0) {  // +0x60
    ((void (*)(void*))this->field_0x6C)(this->field_0x60);  // +0x6C is destructor function pointer
  }
  if (this->field_0x50 != 0) {  // +0x50
    ((void (*)(void*))this->field_0x5C)(this->field_0x50);  // +0x5C is destructor function pointer
  }
  
  // Call global cleanup function
  FUN_0046c640();
}