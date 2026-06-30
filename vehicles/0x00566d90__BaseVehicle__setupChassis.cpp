// FUNC_NAME: BaseVehicle::setupChassis
void __thiscall BaseVehicle::setupChassis(void)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  // Call engine function to create chassis object from member data
  // +0x44 = chassis model data pointer
  // +0x34 = chassis position data
  // +0x40 = chassis rotation data  
  // +0x3c = chassis scale data
  // +0x48 = chassis physics properties
  uVar1 = FUN_00b03980(*(undefined4 *)(this + 0x44),*(undefined4 *)(this + 0x34),
                       *(undefined4 *)(this + 0x40),*(undefined4 *)(this + 0x3c),
                       *(undefined4 *)(this + 0x48));
  
  // Call virtual function at +0x50 to attach chassis to vehicle
  (**(code **)(this + 0x50))(uVar1);
  
  // Initialize the chassis object
  FUN_00b0c100(uVar1);
  
  // Get world collision object from Havok physics
  puVar2 = (undefined4 *)FUN_00ad8d50();
  
  // Store collision object at +0xc
  *(undefined4 **)(this + 0xc) = puVar2;
  
  if (puVar2 != (undefined4 *)0x0) {
    // Call constructor/initializer on collision object
    (**(code **)*puVar2)();
  }
  return;
}