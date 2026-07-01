// FUNC_NAME: GodfatherGameManager::handleGameEvent
undefined4 __thiscall GodfatherGameManager::handleGameEvent(int *this, undefined4 param_2, undefined4 param_3, undefined4 param_4, int eventType, undefined4 param_6)
{
  int iVar1;
  float fVar2;
  undefined4 uVar3;
  float10 fVar4;
  
  if (eventType == 0x23) { // EVENT_TYPE_ENTER_BUILDING
    // Call some method on the building manager (this[0x1e] = buildingManager pointer)
    (**(code **)(*this + 0x2c))(this[0x1e], 1, 0, 0, 0x3f800000, 0x3f800000); // 1.0f, 1.0f
    return 1;
  }
  if (eventType != 0x24) { // EVENT_TYPE_EXIT_BUILDING
    uVar3 = FUN_0073e610(param_2, param_3, param_4, eventType, param_6); // Base class handler
    return uVar3;
  }
  // Handle exit building event
  this[0x20] = this[0x20] + 1; // +0x80: exitCount
  iVar1 = this[0x17]; // +0x5C: pointer to some game state
  fVar4 = (float10)FUN_00716490(); // Get current time
  this[0x22] = (int)(float)fVar4; // +0x88: exitTimestamp
  fVar2 = (float)*(int *)(iVar1 + 0x24bc); // Some game state value at offset 0x24BC
  if (*(int *)(iVar1 + 0x24bc) < 0) {
    fVar2 = fVar2 + DAT_00e44578; // Add negative bias
  }
  this[0x21] = (int)(fVar2 * DAT_00d5efb8); // +0x84: scaled exit value
  return 1;
}