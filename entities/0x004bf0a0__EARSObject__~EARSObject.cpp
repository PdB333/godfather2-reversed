// FUNC_NAME: EARSObject::~EARSObject

void __thiscall EARSObject::~EARSObject(EARSObject* this)
{
  int childObj;
  
  // Zero out some member fields (likely flags/pointers)
  this->field_0x34 = 0;
  this->field_0x08 = 0;
  this->field_0x0C = 0;
  this->field_0x30 = 0;
  
  // If child object exists, destroy it
  if (this->childObjectPtr != 0) {
    childObj = *(int *)(this->childObjectPtr + 0x14); // +0x14 likely another pointer/interface
    if (childObj != 0) {
      FUN_004cb8a0(childObj); // Call destructor on child's resource
    }
    // Call global singleton cleanup function (if registered)
    if (g_globalManager != (undefined4 *)0x0) {
      (**(code **)*g_globalManager)(1); // Dereference and call with arg 1
    }
  }
  // Clear child pointer
  this->childObjectPtr = 0;
  return;
}