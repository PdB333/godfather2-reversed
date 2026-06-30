// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(EARSObject* this)
{
  // +0x00: primary vtable pointer (set to derived class vtable during destruction)
  this->vtable = &gVtable_EARSObject; // PTR_FUN_00e2f7b8
  // +0x34: secondary vtable pointer (set to intermediate base vtable)
  this->secondaryVtable = &gSecondaryVtable_Base; // PTR_LAB_00e2f840

  if (gSomeGlobalManager != 0) {
    // Unregister from manager: (global+8) is probably a manager method pointer
    // this->field_0x50 (param_1[0x14]), this->field_0x54 (param_1[0x15]), type=2, data at this+0x40
    FUN_00415f90(*(undefined4*)(gSomeGlobalManager + 8), this->field_0x50, this->field_0x54, 2, &this->field_0x40);
  }

  if (this->field_0x80 != 0) {
    // Clear a pointer stored in a child object at offset 8, then null the child pointer
    *(undefined4*)(this->field_0x80 + 8) = 0;
    this->field_0x80 = 0;
  }

  // Set secondary vtable to base class for proper destructor chaining
  this->secondaryVtable = &gSecondaryVtable_BaseFinal; // PTR_LAB_00e2f7a8

  // Call base class destructor
  FUN_00415130();
}