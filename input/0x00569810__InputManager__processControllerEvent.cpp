// FUNC_NAME: InputManager::processControllerEvent
void __thiscall InputManager::processControllerEvent(int *this, undefined4 param_2)
{
  int iVar1;
  
  // Acquire input lock (mutex or critical section)
  FUN_00ab4db0(&DAT_00e2cbe8);
  
  // Find controller slot index for this event
  iVar1 = FUN_005695c0(param_2);
  
  // If valid controller slot found
  if (-1 < iVar1) {
    // Call virtual function at vtable+0x40 on the controller object
    // vtable+0x40 is likely processEvent or handleInput
    (**(code **)(*this + 0x40))(this[iVar1 + 0x8a]);  // this + (iVar1 * 4 + 0x228) = controller slot data
  }
  
  // Release input lock
  FUN_00ab4e70();
  return;
}