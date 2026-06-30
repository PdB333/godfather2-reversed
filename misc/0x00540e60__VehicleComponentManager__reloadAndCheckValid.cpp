// FUNC_NAME: VehicleComponentManager::reloadAndCheckValid
void VehicleComponentManager::reloadAndCheckValid(void)
{
  int instancePtr;
  void *componentPtr;
  undefined8 result;
  
  if ((unaff_EDI != 0) && (in_EAX != 0)) {
    // reload the component data
    FUN_005413f0();
    // check if the reload succeeded (likely returns success/failure pair)
    result = FUN_00541430();
    // store the validation result: (result & (result >> 32)) != 0
    // This ANDs the low and high 32 bits of the 64-bit return, checks non-zero
    *unaff_ESI = ((uint)result & (uint)((ulonglong)result >> 0x20)) != 0;
    return;
  }
  // If either pointer is null, default to valid (1)
  *unaff_ESI = 1;
  return;
}