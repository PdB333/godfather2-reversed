// FUNC_NAME: ActionStateManager::processCommand
// Address: 0x0051d020
// Role: Processes action state commands (start, stop, set target, etc.) for an object.
// The input struct (passed in EAX) contains: { int commandType; int param_handle; int param2; float* quaternion; }
// Modifies object state at offsets: +0xb0 (state), +0xb4 (param), +0xb8 (target), +0xbc (quaternion pointer), +0xc0 (effect handle), +0xd0-0xdc (stored quaternion)
// End state is stored and a debug label pointer at +0x78 is set from a table.

void __thiscall ActionStateManager::processCommand(void *this, int *inputParams)
{
  float *floatPtr;
  float w;
  float z;
  float y;
  float x;
  int objectId;
  int paramHandle;
  int state;
  int newState = 0;
  float localQuat[4]; // local_1c, local_18, local_14

  int cmdType = *inputParams; // first dword is command type
  switch (cmdType) {
    case 1: // start action?
    case 2:
    case 3:
    case 4:
      objectId = inputParams[1]; // handle to object/effect
      if (objectId != 0) {
        *(int *)((char *)this + 0xb4) = objectId; // store object handle
        FUN_0044b210(objectId); // likely addRef (increment ref count)
        floatPtr = (float *)inputParams[3]; // pointer to quaternion (x,y,z,w)
        if ((floatPtr != (float *)0x0) &&
           (((*floatPtr != 0.0f || (floatPtr[1] != 0.0f)) || (floatPtr[2] != 0.0f)))) {
          // store quaternion into object's buffer at +0xd0
          x = floatPtr[0];
          y = floatPtr[1];
          z = floatPtr[2];
          w = floatPtr[3];
          *(float *)((char *)this + 0xd0) = x;
          *(float *)((char *)this + 0xd4) = y;
          *(float *)((char *)this + 0xd8) = z;
          *(float *)((char *)this + 0xdc) = w;
          *(float **)((char *)this + 0xbc) = (float *)((char *)this + 0xd0); // point to local copy
        }
        state = FUN_004e92e0(); // check if game is active?
        if (inputParams[2] < 1) {
          int v6 = *(int *)(*(int *)((char *)this + 0x10) + 0x2c); // object type?
          if (((v6 == 0) || (state == 0)) || (v6 = FUN_004c3df0(v6), v6 < 0)) {
            newState = 1;
          } else {
            *(int *)((char *)this + 0xb8) = v6; // store target handle
            newState = 2;
          }
        } else {
          *(int *)((char *)this + 0xb8) = inputParams[2]; // store explicitly given target
          newState = cmdType;
        }
        if (state == 0) {
          newState = 1;
          *(undefined4 *)((char *)this + 0xb8) = 0xffffffff;
        } else if ((*(unsigned int *)(*(int *)((char *)this + 0x10) + 0x14) & 0x40000000) != 0) {
          // check flag: is effect spawnable?
          localQuat[0] = 0.0f;
          localQuat[1] = 0.0f;
          localQuat[2] = 0.0f;
          if (DAT_0116407c != (undefined4 *)0x0) {
            localQuat[2] = *(float *)DAT_0116407c;
            localQuat[0] = *(float *)(DAT_0116407c + 1); // actually it's reading two dwords as floats
          }
          int effectId = FUN_00536ed0(*(undefined4 *)((char *)this + 0xb8), &localQuat);
          if (effectId != 0) {
            newState = 4;
            *(int *)((char *)this + 0xc0) = effectId; // store effect handle
          }
        }
      }
      break;
    case 5: // stop/cleanup action?
      *(int *)((char *)this + 0xb4) = inputParams[1];
      floatPtr = (float *)inputParams[3];
      newState = 5;
      if ((floatPtr != (float *)0x0) && 
         (((*floatPtr != 0.0f || (floatPtr[1] != 0.0f)) || (floatPtr[2] != 0.0f)))) {
        x = floatPtr[0];
        y = floatPtr[1];
        z = floatPtr[2];
        w = floatPtr[3];
        *(float *)((char *)this + 0xd0) = x;
        *(float *)((char *)this + 0xd4) = y;
        *(float *)((char *)this + 0xd8) = z;
        *(float *)((char *)this + 0xdc) = w;
        *(float **)((char *)this + 0xbc) = (float *)((char *)this + 0xd0);
      }
  }
  // If previous state was 4 and we have an effect handle, release it
  if ( (*(int *)((char *)this + 0xb0) == 4) && (*(int *)((char *)this + 0xc0) != 0) ) {
    (**(code **)(*DAT_01194538 + 4))(*(int *)((char *)this + 0xc0), 0); // call release function
    *(undefined4 *)((char *)this + 0xc0) = 0;
  }
  *(int *)((char *)this + 0xb0) = newState; // store new state
  *(undefined **)((char *)this + 0x78) = (&PTR_LAB_00e38260)[newState]; // debug label table
  return;
}