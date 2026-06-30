// FUNC_NAME: ManagerClass::Constructor
undefined4 * __fastcall ManagerClass::Constructor(ManagerClass *this)
{
  int *subObjectPtr;
  
  // Set initial flags
  this->field_0x04 = 1;               // +0x04: some flag
  this->field_0x08 = 0;               // +0x08: counter or state
  this->field_0x0C = &PTR_LAB_00d5d898; // +0x0C: function table pointer (initial)
  
  // Store global singleton reference
  g_GlobalManager = this;              // DAT_011299b4 = this
  
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d5d8b8;    // +0x00: vtable
  
  // Update function table pointer
  this->field_0x0C = &PTR_LAB_00d5d8b4; // +0x0C: final function table
  
  // Zero out fields at offsets 0x10 and 0x14, 0x18, 0x1C
  *(byte *)&this->field_0x10 = 0;     // +0x10: byte field
  subObjectPtr = &this->field_0x14;   // +0x14: pointer to sub-object (int*)
  *subObjectPtr = 0;                  // +0x14: sub-object pointer initially null
  this->field_0x18 = 0;               // +0x18: some int
  this->field_0x1C = 0;               // +0x1C: some int
  *(byte *)&this->field_0x20 = 0;     // +0x20: byte field
  
  // If sub-object pointer was previously allocated, free it
  if (*subObjectPtr != 0) {
    FUN_004daf90(subObjectPtr);        // Free sub-object at +0x14
    *subObjectPtr = 0;
  }
  
  this->field_0x1C = 0;               // +0x1C: reset again
  return this;
}