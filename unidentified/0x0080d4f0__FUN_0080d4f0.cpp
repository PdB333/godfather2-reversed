// FUNC_NAME: SomeGameObject::destructor
void __fastcall SomeGameObject::destructor(SomeGameObject *this) // 0x0080d4f0
{
  int *piVar1;
  int iVar2;
  
  // Set vtable pointer
  this->vtable = &PTR_LAB_00d72c30;
  
  // Call parent destructors/cleanup
  FUN_007fbe50(); // likely base class destructor
  
  // Release allocated resources
  FUN_007f6420(0x49); // release resource type 0x49
  FUN_007f6420(0x5c); // release resource type 0x5c
  
  // Destroy member object at +0x98 (param_1[0x26])
  FUN_005512c0(this->field_0x98); // +0x98
  
  // Check flag at +0x94 (param_1[0x25]) bit 1
  if (((uint)this->field_0x94 >> 1 & 1) != 0) {
    // Call cleanup method on object at +0x50
    (**(code **)(*(int *)this->field_0x50 + 0x234))(4,1); // +0x50
  }
  
  piVar1 = &this->field_0x58; // +0x58 (param_1 + 0x16)
  
  // Decrement reference count on object at +0x58 if valid and not 0x48
  if ((this->field_0x58 != 0) && (this->field_0x58 != 0x48)) {
    if (*piVar1 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1 + -0x48; // subtract 0x48 to get base pointer
    }
    *(char *)(iVar2 + 0x1e4) = *(char *)(iVar2 + 0x1e4) + -1; // decrement reference at +0x1e4
  }
  
  // Cleanup specific to this class
  FUN_0080e700(1);
  
  // Destroy member objects if allocated
  if (this->field_0x60 != 0) { // +0x60 (param_1[0x18])
    FUN_004daf90(&this->field_0x60);
  }
  if (*piVar1 != 0) { // +0x58
    FUN_004daf90(piVar1);
  }
  
  // Final cleanup
  FUN_0080ea60();
  return;
}