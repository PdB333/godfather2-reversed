// FUNC_NAME: VehicleAI::updateSeekBehavior
void __fastcall VehicleAI::updateSeekBehavior(int thisPtr)
{
  int *pData;
  uint *pFlags;
  float localVec[3];
  float deltaVec[3];
  float currentPos[3];
  float normVec[3];

  // Dereference vtable call: get data pointer from some handle system
  // param_1+0x10c is likely a pointer to a data manager or pool
  // param_1+0x14c is an index or handle
  pData = (int *)(**(code **)(**(int **)(thisPtr + 0x10c) + 0xc))(*(undefined4 *)(thisPtr + 0x14c));
  
  int node = *pData;
  undefined4 savedPrev = 0;
  if (node != 0) {
    savedPrev = *(undefined4 *)(node + 4);
    *(int **)(node + 4) = &node; // Push current node onto stack-local list
  }
  
  undefined8 *pVec = (undefined8 *)pData[2]; // Pointer to a 3D vector (x,y packed as two ints, z as float)
  if (node != 0) {
    // Extract target position from pVec
    undefined8 rawXY = *pVec;
    float targetZ = *(float *)(pVec + 1);
    
    // Get current position from some system (FUN_007577e0)
    FUN_007577e0(currentPos, currentPos+1, currentPos+2);
    
    // Compute delta vector
    deltaVec[0] = (float)(uint)(rawXY & 0xFFFFFFFF) - currentPos[0]; // rawXY low int
    deltaVec[1] = (float)(uint)(rawXY >> 32) - currentPos[1];       // rawXY high int
    deltaVec[2] = targetZ - currentPos[2];
    
    // Normalize delta
    FUN_0056afa0(deltaVec, deltaVec);
    
    // Clear bit 0 of some flag at offset 0xb4 from thisPtr+0x100
    pFlags = (uint *)(*(int *)(thisPtr + 0x100) + 0xb4);
    *pFlags = *pFlags & 0xfffffffe;
    
    // Apply desired velocity/force (first arg is from data manager, second is handle, then two vectors, then zero)
    FUN_00601050(*(undefined4 *)(thisPtr + 0x10c), *(undefined4 *)(thisPtr + 0x14c), currentPos, deltaVec, 0);
    
    // Set speed to 1.0f (0x3f800000) with no blending or something
    FUN_005fea00(1.0f, 0);
    
    // Cleanup: pop node from stack list
    if (node != 0) {
      FUN_004daf90(&node);
    }
  }
  return;
}