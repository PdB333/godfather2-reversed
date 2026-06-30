// FUNC_NAME: ManagerClass::constructor
void __thiscall ManagerClass::constructor(ManagerClass* this)
{
  int* piVar1;
  
  // Set initial vtable (base class vtable)
  this->vtable = (void*)&PTR_FUN_00e35830;
  this->field_0x04 = (void*)&PTR_LAB_00e35878;  // +0x04: second vtable or member
  // Call constructors for member objects / base classes
  FUN_004086d0(&DAT_01206970);
  FUN_004086d0(&DAT_01206978);
  FUN_00408310(&DAT_01218020);
  FUN_00408310(&DAT_01218028);
  // Two-phase construction: pass pointer to self
  ManagerClass* pThis = this;
  FUN_00423bf0(&pThis);
  // Insert into global list (DAT_01206880 likely a global manager struct)
  piVar1 = (int*)(DAT_01206880 + 0x14);  // +0x14: pointer to list head or array
  **(void***)(DAT_01206880 + 0x14) = &PTR_LAB_01124500;
  *piVar1 = *piVar1 + 4;
  *(void**)*piVar1 = this;  // store this pointer in list
  *piVar1 = *piVar1 + 4;
  // Additional initialization
  FUN_004083d0();
  // Set final vtable (derived class vtable)
  this->vtable = (void*)&PTR_LAB_00e357e8;
  return;
}