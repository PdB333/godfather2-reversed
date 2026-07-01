// FUNC_NAME: ChaseCamera::initializeFromParams
undefined4 * __thiscall ChaseCamera::initializeFromParams(undefined4 *this, undefined4 param_2, int param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  
  // Call base class initializer (likely Camera::init or similar)
  FUN_008cde60(param_2,param_3);
  
  // Load global chase camera settings
  uVar2 = _DAT_00d5780c;
  uVar3 = 0;
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7c910;
  
  // +0xD0: Set initial state flag (1 = enabled/active)
  *(undefined1 *)(this + 0x34) = 1;
  
  // +0xD4: Store chase camera settings pointer
  this[0x35] = uVar2;
  
  // Search through parameter list for specific camera type
  if (*(short *)(param_3 + 0x20) != 0) {
    do {
      puVar1 = *(undefined4 **)(*(int *)(param_3 + 0x1c) + uVar3 * 4);
      // Check for camera type ID: 0x9534C6CB (likely ChaseCamera type)
      if (puVar1[4] == -0x6acb3935) {
        this[0x35] = *puVar1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(ushort *)(param_3 + 0x20));
  }
  
  // Load another global setting (likely camera FOV or distance)
  uVar2 = DAT_01205228;
  
  // +0x04: Store reference to something (parent/owner?)
  this[0x37] = this[1];
  
  // +0xD8: Store additional camera parameter
  this[0x36] = uVar2;
  
  return this;
}