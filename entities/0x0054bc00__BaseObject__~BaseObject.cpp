// FUNC_NAME: BaseObject::~BaseObject
void __thiscall BaseObject::~BaseObject(BaseObject *this)
{
  uint allocFlag; // offset +0x18 (uVar1)
  
  // Switch vtable to derived class stub to prevent virtual calls during destruction
  this->vtable = &PTR_LAB_00e397fc;
  
  allocFlag = this->field_0x18; // read allocation flag / size data
  if ((int)allocFlag >= 0) {
    // Ensure thread-local storage is available (TlsGetValue side effect)
    TlsGetValue(DAT_01139810);
    // Free the allocated memory block: pointer at +0x10, size = (allocFlag & 0x3fffffff) * 0x30, pool ID = 0x17
    FUN_00aa26e0(this->field_0x10, (allocFlag & 0x3fffffff) * 0x30, 0x17);
  }
  
  // Switch vtable to base class stub
  this->vtable = &PTR_LAB_00dc4710;
  return;
}