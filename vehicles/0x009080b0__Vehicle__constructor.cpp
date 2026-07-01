// FUNC_NAME: Vehicle::constructor
void __thiscall VehicleConstructor(Vehicle *this)
{
  // Set vtable to Vehicle's vtable at 0x00d83028
  this->vtable = &PTR_FUN_00d83028;
  
  // Set some pointers - likely base class or interface pointers
  // +0x0C (param_1[3]) -> vtable at 0x00d83024
  this->baseVtable2 = &PTR_LAB_00d83024;
  
  // +0x10 (param_1[4]) -> vtable at 0x00d83014
  this->baseVtable3 = &PTR_LAB_00d83014;
  
  // Call base class constructor (likely BaseVehicle)
  FUN_00907f20();
  
  // Update vtable pointers after base constructor
  // +0x10 -> vtable at 0x00e30fe0
  this->baseVtable3 = &PTR_LAB_00e30fe0;
  
  // +0x0C -> vtable at 0x00d83010
  this->baseVtable2 = &PTR_LAB_00d83010;
  
  // Clear global flag DAT_0112ff6c
  DAT_0112ff6c = 0;
  
  // Call some initialization function
  FUN_004083d0();
  
  return;
}