// FUNC_NAME: WheeledVehicle::constructor

undefined4 * __thiscall WheeledVehicle::constructor(WheeledVehicle *this, undefined4 param_2, undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  // Call base class constructor (likely Entity or Sentient)
  FUN_004ac120(param_2, param_3);
  
  // Set vtable pointer
  *this = (undefined4 *)&PTR_LAB_00d65334;
  
  // Clear various fields
  this->field_0x18 = 0;               // +0x60
  this->field_0x19 = 0;               // +0x64
  *(byte *)(this + 0x1d) = 0;         // +0x74 (bool/byte)
  this->field_0x22 = 0;               // +0x88
  
  // If this->field_0x12 (+0x48) is non-zero, compute an offset
  if (this->field_0x12 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = this->field_0x12 - 0x48;  // Subtract base size (0x48 bytes)
  }
  this->field_0x1e = iVar3;           // +0x78
  
  // If computed offset is not zero, get a pointer from global
  if (iVar3 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0043b870(DAT_0112afe8);  // Possibly allocate or get interface
  }
  uVar1 = _DAT_00d5780c;
  
  this->field_0x1f = uVar2;           // +0x7c
  this->field_0x20 = this->field_0x1e + 0x3c0;  // +0x80 = offset + 960
  this->field_0x21 = uVar1;           // +0x84
  
  return this;
}