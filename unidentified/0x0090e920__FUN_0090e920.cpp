// FUNC_NAME: UnknownClass::destructor
void __fastcall UnknownClass::destructor(UnknownClass *this)
{
  // Set up vtable pointers
  this->vtable = &PTR_FUN_00d83770;  // +0x00: vtable pointer
  this->field_0x3c = &PTR_LAB_00d83760;  // +0x3C
  this->field_0x48 = &PTR_LAB_00d8375c;  // +0x48
  
  // Call destructors for sub-objects
  FUN_004086d0(&DAT_012069c4);  // Some static/global destructor
  FUN_004086d0(&this->field_0x60);  // +0x60
  FUN_00408310(&this->field_0x60);  // +0x60
  
  FUN_004086d0(&this->field_0x68);  // +0x68
  FUN_00408310(&this->field_0x68);  // +0x68
  
  FUN_004086d0(&this->field_0x70);  // +0x70
  FUN_00408310(&this->field_0x70);  // +0x70
  
  FUN_004086d0(&this->field_0x78);  // +0x78
  FUN_00408310(&this->field_0x78);  // +0x78
  
  FUN_00408310(&this->field_0x50);  // +0x50
  FUN_00408310(&this->field_0x58);  // +0x58
  
  // Check flags and release resources
  if (((this->flags & 8) != 0) && ((this->flags & 1) != 0) && (this->resourceId != -1)) {
    FUN_0090dff0(this->resourceId);  // Release resource
    this->resourceId = 0xffffffff;
  }
  
  // Delete managed objects via function pointers
  if (this->object1 != 0) {
    ((void (*)(void *))this->object1Deleter)(this->object1);
  }
  if (this->object2 != 0) {
    ((void (*)(void *))this->object2Deleter)(this->object2);
  }
  
  FUN_0046c640();  // Some cleanup function
}