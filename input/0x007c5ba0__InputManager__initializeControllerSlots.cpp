// FUNC_NAME: InputManager::initializeControllerSlots
undefined4 * __thiscall InputManager::initializeControllerSlots(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  int iVar1;
  undefined4 *puVar2;
  
  // Call base class constructor or initialization
  FUN_007ab5e0(param_2, param_3);
  
  // Set vtable pointer
  *this = &PTR_LAB_00d6e84c;
  
  // Initialize controller slot states (0x1d = +0x74, 0x1e = +0x78, etc.)
  this[0x1d] = 0;  // +0x74 - controllerFlags[0]
  this[0x1e] = 0;  // +0x78 - controllerFlags[1]
  this[0x1f] = 0;  // +0x7c - controllerFlags[2]
  this[0x20] = 0;  // +0x80 - controllerFlags[3]
  this[0x21] = 0;  // +0x84 - controllerFlags[4]
  this[0x22] = 0;  // +0x88 - controllerFlags[5]
  this[0x23] = 0;  // +0x8c - controllerFlags[6]
  this[0x24] = 0;  // +0x90 - controllerFlags[7]
  
  // Get input device manager instance
  iVar1 = FUN_007ab130();  // InputDeviceManager::getInstance
  this[0x1e] = *(undefined4 *)(iVar1 + 4);  // Store device count or ID
  
  // Call method on input device manager
  puVar2 = (undefined4 *)FUN_007ab130();  // InputDeviceManager::getInstance
  (**(code **)*puVar2)(0x3f);  // InputDeviceManager::enumerateDevices(63)
  
  // Check for XInput controller availability
  iVar1 = FUN_007ab150();  // XInputManager::getInstance
  if ((*(byte *)(iVar1 + 4) & 1) != 0) {  // Check if XInput is available
    this[0x1d] = this[0x1d] | 1;  // Set first controller slot as active
    puVar2 = (undefined4 *)FUN_007ab150();  // XInputManager::getInstance
    (**(code **)*puVar2)(1);  // XInputManager::enableController(1)
  }
  
  return this;
}