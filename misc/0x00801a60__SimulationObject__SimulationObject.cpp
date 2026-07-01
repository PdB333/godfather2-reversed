// FUNC_NAME: SimulationObject::SimulationObject
undefined4 * __thiscall SimulationObject::SimulationObject(undefined4 *this, int createFlag)
{
  undefined4 extraObj;

  if (createFlag == 0) {
    extraObj = 0;
  }
  else {
    extraObj = FUN_00481610();  // Allocate additional data/object (e.g., memory pool)
  }
  FUN_0064d390(0,1);           // Init critical section or mutex (arg0=0, arg1=1)
  *this = &PTR_LAB_00e317dc;   // Set primary vtable (base class)
  this[6] = 0;                 // +0x18: some flag or counter
  FUN_00454a10(extraObj);      // Initialize with extra object/handle
  this[9] = 1;                 // +0x24: active/initialized flag
  *this = &PTR_LAB_00d71eac;   // Override vtable (derived class or second base)
  this[0xd] = 0;              // +0x34: some state or pointer
  this[10] = &PTR_LAB_00d71d34;// +0x28: store address of secondary vtable pointer (for interface or covariant return)
  this[0xc] = &LAB_007fa6e0;  // +0x30: store function pointer (e.g., update/process routine)
  FUN_0084d330();             // Post-construction initialization (e.g., register with manager)
  this[5] = this + 10;        // +0x14: store pointer to subobject at offset 0x28 (self-reference for iterator)
  return this;
}