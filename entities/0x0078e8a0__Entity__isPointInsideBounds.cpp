// FUNC_NAME: Entity::isPointInsideBounds
undefined4 __thiscall Entity::isPointInsideBounds(int this, undefined4 *point)
{
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  float local_18;
  
  local_30 = *point;
  local_2c = point[1];
  local_28 = point[2];
  local_24 = _DAT_00d5780c; // +0x??: some global Z offset or padding
  FUN_0056b420(this + 0x50, &local_30, &local_20); // Transform point into local space (likely worldToLocal)
  // Check if transformed point is within bounding box defined by global min/max bounds
  if ((((DAT_00e44718 <= local_20) && (local_20 <= _DAT_00d5c458)) && (DAT_00e44718 <= local_1c)) &&
     (((local_1c <= _DAT_00d5c458 && (DAT_00e44718 <= local_18)) && (local_18 <= _DAT_00d5c458)))) {
    return 1;
  }
  return 0;
}