// FUNC_NAME: InputDeviceManager::InputDeviceManager
undefined4 * __thiscall InputDeviceManager::InputDeviceManager(InputDeviceManager *this, undefined4 param_2)
{
  InputDeviceManager *deviceArray;
  InputDeviceManager *currentDevice;
  int deviceIndex;
  undefined4 *local_4;
  
  // Set up vtable pointers and initial states
  deviceArray = this + 3; // +0x0C offset for vtable pointer?
  this->field_0x04 = 1;
  this->field_0x08 = 0;
  *deviceArray = &PTR_LAB_00e30fe0; // vtable for manager?
  *this = &PTR_FUN_00d6105c; // base class vtable?
  *deviceArray = &PTR_LAB_00d6104c; // corrected vtable
  this->field_0x10 = 0;
  
  // Initialize 11 input device slots (each 0x14 bytes)
  currentDevice = this + 5; // +0x14
  deviceIndex = 10;
  do {
    *currentDevice = &PTR_FUN_00d6102c; // device vtable
    currentDevice->field_0x04 = 0;
    currentDevice->field_0x08 = 0;
    currentDevice->field_0x0C = 0;
    currentDevice->field_0x10 = 1; // active flag?
    currentDevice = currentDevice + 5; // increment by 0x14 bytes
    deviceIndex = deviceIndex - 1;
  } while (-1 < deviceIndex);
  
  // Zero out additional fields
  *(byte *)(this + 0x3f) = 0; // byte at offset 0xFC
  this->field_0x100 = 0;
  this->field_0x104 = 0;
  this->field_0x108 = 0;
  this->field_0x10C = 0;
  this->field_0x114 = 0;
  *(byte *)((int)this + 0x145) = 0; // byte at offset 0x145
  
  local_4 = this;
  
  // Connect a global signal/handler (DAT_012069c4)
  if (DAT_012069c4 != 0) {
    FUN_00408900(this, &DAT_012069c4, 0x8000);
  }
  
  // Look up message "iMsgInfiniteAmmoUnlocked" and connect if exists
  FUN_00408240(&DAT_0112ab34, "iMsgInfiniteAmmoUnlocked");
  if (DAT_0112ab34 != 0) {
    FUN_00408900(this, &DAT_0112ab34, 0x8000);
  }
  
  // Clamp some mission/reputation values
  this->field_0x9C = 4;
  if (4 < (uint)this->field_0x98) {
    this->field_0x98 = 4;
  }
  this->field_0xB0 = 3;
  if (3 < (uint)this->field_0xAC) {
    this->field_0xAC = 3;
  }
  this->field_0xC4 = 1;
  if (1 < (uint)this->field_0xC0) {
    this->field_0xC0 = 1;
  }
  this->field_0xF8 = 10;
  
  // Zero out more fields (likely vectors or sequences)
  *(undefined8 *)(this + 0x46) = 0; // 8 bytes at offset 0x118
  *(undefined8 *)(this + 0x48) = 0; // 0x120
  *(undefined8 *)(this + 0x4a) = 0; // 0x128
  *(undefined8 *)(this + 0x4c) = 0; // 0x130
  *(undefined2 *)(this + 0x4e) = 0; // 2 bytes at 0x138
  *(byte *)((int)this + 0x13a) = 0; // byte at 0x13A
  
  // Register a hashable object (maybe input device?)
  local_4 = (undefined4 *)0x0;
  if (FUN_00463a80(0x5beea32a, &local_4) == 0) {
    FUN_00463980(0x5beea32a, deviceArray, param_2);
    *(byte *)((int)this + 0x145) = 1; // mark as registered
  }
  
  // Final cleanup
  *(byte *)(this + 0x144) = 0; // field at offset 0x144
  this->field_0x140 = 0;
  this->field_0x13C = 0;
  *(byte *)(this + 0xF4) = 0; // field at offset 0xF4
  
  return this;
}