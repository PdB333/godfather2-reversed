// FUNC_NAME: ComponentBase::constructor
undefined4 * __thiscall ComponentBase::constructor(ComponentBase *this, undefined4 param_2, undefined4 param_3)
{
  char cVar1;
  uint uVar2;
  int *piVar3;
  int unaff_EDI;
  uint unaff_retaddr;
  
  // Call base class constructor (assumed to be a generic initializer)
  FUN_004ac120(param_2, param_3);
  
  // Set vtable pointer
  *this = &PTR_LAB_00d67f24; // vtable for ComponentBase
  
  // Zero-initialize fields at offsets 0x50 through 0x68
  this->field_0x50 = 0; // param_1[0x14]
  this->field_0x54 = 0; // param_1[0x15]
  this->field_0x58 = 0; // param_1[0x16]
  this->field_0x5C = 0; // param_1[0x17]
  this->field_0x60 = 0; // param_1[0x18]
  this->field_0x64 = 0; // param_1[0x19]
  this->field_0x68 = 0; // param_1[0x1A]
  
  // Check if a pointer at offset 0x48 is valid
  if (this->field_0x48 == 0) {
    piVar3 = (int *)0x0;
  }
  else {
    // The pointer at offset 0x48 is actually offset +0x48 from some base (piVar3)
    piVar3 = (int *)(this->field_0x48 - 0x48);
  }
  
  param_3 = 0;
  cVar1 = (**(code **)(*piVar3 + 0x10))(0x3a8fda85, &param_3); // virtual call with hash
  uVar2 = -(uint)(cVar1 != '\0') & unaff_retaddr;
  this->field_0x50 = uVar2; // set based on result
  
  if (this->field_0x50 != 0) {
    if (this->field_0x48 == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(this->field_0x48 - 0x48);
    }
    (**(code **)(*piVar3 + 0x10))(0x383225a1, &stack0x00000000); // another virtual call
  }
  
  if (this->field_0x50 != 0) {
    if (this->field_0x48 == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(this->field_0x48 - 0x48);
    }
    cVar1 = (**(code **)(*piVar3 + 0x10))(0x369ac561, &stack0x00000000); // third virtual call
    if ((cVar1 != '\0') && (unaff_EDI != 0)) {
      this->field_0x64 = this->field_0x64 | 0x10; // set bit 4 on field at +0x64
      return this;
    }
  }
  
  return this;
}