// FUNC_NAME: ChaseCamera::initialize
undefined4 * __thiscall ChaseCamera::initialize(undefined4 *this, undefined4 *params)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int in_EAX;
  int iVar4;
  int unaff_FS_OFFSET;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  
  // Base class initialization
  CameraManager::someInit();
  
  // Set vtable pointer
  *this = &ChaseCamera_vtable;
  
  if (*(char *)(in_EAX + 0xd) == '\0') {
    // Get thread local storage offset
    iVar4 = **(int **)(unaff_FS_OFFSET + 0x2c);
    
    // Store params pointer
    iVar2 = this[4];
    this[9] = params;
    
    iVar3 = *(int *)(iVar4 + 8);
    piVar1 = (int *)(iVar4 + 8);
    
    // Process camera parameters
    if ((*(byte *)(params + 8) & 1) == 0) {
      // Absolute position
      *(undefined4 *)(iVar2 + 0x40 + iVar3) = params[0xb];
      *(undefined4 *)(this[4] + 0x44 + *piVar1) = params[0xc];
      *(undefined4 *)(this[4] + 0x48 + *piVar1) = params[0xd];
    }
    else {
      // Relative position (add to current)
      *(float *)(iVar2 + 0x40 + iVar3) = (float)params[0xb] + *(float *)(iVar2 + 0x40 + iVar3);
      *(float *)(this[4] + 0x44 + *piVar1) =
           (float)params[0xc] + *(float *)(this[4] + 0x44 + *piVar1);
      *(float *)(this[4] + 0x48 + *piVar1) =
           (float)params[0xd] + *(float *)(this[4] + 0x48 + *piVar1);
    }
    
    // Set some field (maybe distance or speed)
    *(undefined4 *)(this[4] + 0x4c + *piVar1) = someGlobalFloat;
    
    // Transform rotation data
    FUN_0056b8a0((float)params[0xe] * someGlobalFloat2,
                 (float)params[0xf] * someGlobalFloat2,
                 (float)params[0x10] * someGlobalFloat2,
                 this[4] + 0x10 + *piVar1);
    
    // More base class initialization
    CameraManager::someOtherInit();
    
    this[10] = 0;  // Clear string/null for follow target
    
    // Try to create follow target
    iVar4 = ChaseCamera::createFollowTarget();
    if (iVar4 != 0) {
      // Initialize collision detection data
      local_20 = *params;
      local_1c = params[1];
      local_30 = params[10];
      local_18 = params[2];
      local_14 = this[1];
      local_28 = local_30;
      local_2c = local_30;
      
      if ((*(byte *)(params + 8) & 2) != 0) {
        local_2c = params[0x14];
        local_28 = params[0x15];
      }
      local_24 = someGlobalFloat;
      
      iVar4 = ChaseCamera::setupCollision(&local_20, &local_30, 
                                           this[4] + *piVar1 + 0x50,
                                           *(undefined4 *)(*(int *)(local_14 + 0x10) + 0x20));
      this[10] = iVar4;
      
      if (iVar4 != 0) {
        this[0xb] = params[9];  // Store some parameter
        this[0xc] = 0;          // Clear another field
        return this;
      }
    }
    
    // Mark as invalid/error
    *(uint *)(this[4] + *piVar1) = *(uint *)(this[4] + *piVar1) | 1;
  }
  
  return this;
}