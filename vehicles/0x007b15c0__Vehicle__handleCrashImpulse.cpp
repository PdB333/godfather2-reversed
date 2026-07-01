// FUNC_NAME: Vehicle::handleCrashImpulse
undefined4 Vehicle::handleCrashImpulse(int thisPtr,int *impulseData)

{
  int result;
  char isValid;
  int crashType;
  int unaff_EBX;
  
  result = thisPtr;
  if ((thisPtr != 0) && (impulseData != (int *)0x0)) {
    thisPtr = 0;
    // Call virtual function at vtable+0x10 to validate impulse data (0x369ac561 is a guid/type check)
    isValid = (**(code **)(*impulseData + 0x10))(0x369ac561,&thisPtr);
    if ((isValid != '\0') && (unaff_EBX != 0)) {
      crashType = FUN_00734340(result);  // Get crash type (1=light, 2=heavy)
      if (crashType == 1) {
        // Set light crash flag at +0x24a4
        *(uint *)(result + 0x24a4) = *(uint *)(result + 0x24a4) | 2;
        return 1;
      }
      if (crashType == 2) {
        // Set heavy crash flag at +0x24a4
        *(uint *)(result + 0x24a4) = *(uint *)(result + 0x24a4) | 4;
        return 1;
      }
    }
  }
  return 0;
}