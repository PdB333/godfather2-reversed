// FUNC_NAME: Player::getSomeFloatValue
void Player::getSomeFloatValue(float *outValue)
{
  undefined4 *vtablePtr;
  int esi;
  char result;
  float10 calcValue;
  
  vtablePtr = (undefined4 *)((int)this + 0x100); // +0x100: some member pointer
  *outValue = 0.0f;
  
  // Call virtual function at vtable offset 0x10 with some identifier
  result = (**(code **)(*(int *)*vtablePtr + 0x10))(0x383225a1, &outValue);
  
  if ((result != '\0') && (esi != 0)) {
    // esi likely points to some game manager or player state
    // +0x2888: some member offset in that object
    calcValue = (float10)FUN_006e3f90((int)this, unaff_retaddr, *(undefined4 *)(esi + 0x2888),
                                      _DAT_00d5fa88, DAT_00d5ccf8);
    *outValue = (float)calcValue;
    return;
  }
  
  *outValue = 0.0f;
  return;
}