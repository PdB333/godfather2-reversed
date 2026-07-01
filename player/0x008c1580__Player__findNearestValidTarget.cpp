// FUNC_NAME: Player::findNearestValidTarget
int* __thiscall Player::findNearestValidTarget(int* thisPlayer, int* targetParam, int param3, int param4)
{
  int* currentTarget;
  int* bestTarget;
  char isValid;
  int entity;
  int* targetList;
  int otherEntity;
  float dx, dy, dz;
  float distSq;
  float bestDistSq;
  int* returnTarget;

  currentTarget = targetParam;
  returnTarget = (int*)0x0;
  
  // First check if targetParam is a valid enemy for the local player
  if (((((targetParam != (int*)0x0) && (entity = FUN_0043b870(DAT_01131040), entity != 0)) &&
       (otherEntity = *(int*)(entity + 0x1c), otherEntity != 0)) &&
      ((targetList = (int*)(otherEntity + -0x48), targetList != (int*)0x0 &&
       ((*(uint*)(otherEntity + 0x898) >> 0x17 & 1) != 0)))) &&
     ((currentTarget != targetList && (isValid = FUN_008bf630(currentTarget, targetList, param3, param4), isValid != '\0')))) {
    return targetList; // Direct validation succeeded
  }
  
  // Scan all entities to find nearest valid target
  bestDistSq = DAT_00d5ccf8; // Large initial value / max range
  entity = FUN_00471610(); // Get entity manager or world data
  targetList = (int*)FUN_0043c2c0(*(undefined4*)(thisPlayer + 0x88)); // Get linked list head
  targetList = (int*)*targetList;
  
  if (targetList == (int*)0x0) {
    return (int*)0x0;
  }
  
  do {
    if ((int*)*targetList != currentTarget) {
      // Check if this entity is at war with the target
      targetParam = (int*)0x0;
      isValid = (**(code**)(*(int*)*targetList + 0x10))(0x55859efa, &targetParam); // Call virtual function at offset 0x10
      currentTarget = targetParam;
      
      if (((isValid != '\0') && (targetParam != (int*)0x0)) &&
         ((((uint)targetParam[0x238] >> 0x17 & 1) != 0 && // Check some flag at offset 0x238
          (isValid = FUN_008bf630(targetParam, currentTarget, param3, param4), isValid != '\0')))) {
        // Calculate distance squared
        otherEntity = FUN_00471610();
        dx = *(float*)(otherEntity + 0x30) - *(float*)(entity + 0x30);
        dy = *(float*)(otherEntity + 0x34) - *(float*)(entity + 0x34);
        dz = *(float*)(otherEntity + 0x38) - *(float*)(entity + 0x38);
        distSq = dz * dz + dy * dy + dx * dx;
        
        if ((distSq < bestDistSq) || (bestDistSq == DAT_00d5ccf8)) {
          returnTarget = targetParam;
          bestDistSq = distSq;
        }
      }
    }
    targetList = (int*)targetList[1]; // Next node in linked list
  } while (targetList != (int*)0x0);
  
  return returnTarget;
}