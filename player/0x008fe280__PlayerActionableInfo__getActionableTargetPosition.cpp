// FUNC_NAME: PlayerActionableInfo::getActionableTargetPosition
undefined4 __thiscall PlayerActionableInfo::getActionableTargetPosition(int this, undefined8 *outPosition)
{
  undefined4 result;
  int targetIndex;
  
  // Check if the "disabled" flag is set (bit 4 of byte at +0xD0)
  if ((*(byte *)(this + 0xd0) >> 4 & 1) != 0) {
    return 0;
  }
  
  result = FUN_008fe1e0(); // likely getCurrentActionableTarget()
  
  // Check if we have a valid target type (not 0 and not 0x48 = 72 = unknown sentinel)
  if (((*(int *)(this + 200) != 0) && (*(int *)(this + 200) != 0x48)) &&
     (targetIndex = FUN_00791300(), targetIndex != 0)) {
    // Get position from some entity via FUN_00791300 (getEntityByIndex?) and FUN_00471610 (getTransform?)
    FUN_00791300();
    targetIndex = FUN_00471610();
    *outPosition = *(undefined8 *)(targetIndex + 0x30); // position x,y
    *(undefined4 *)(outPosition + 1) = *(undefined4 *)(targetIndex + 0x38); // position z
    return 1;
  }
  
  // Fallback: get position from some other system
  targetIndex = FUN_006b0ee0(result); // likely getTargetPositionFromSystem
  if (targetIndex != 0) {
    *outPosition = *(undefined8 *)(targetIndex + 0x10); // position x,y
    *(undefined4 *)(outPosition + 1) = *(undefined4 *)(targetIndex + 0x18); // position z
    return 1;
  }
  
  return 0;
}