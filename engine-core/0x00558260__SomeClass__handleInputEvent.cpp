// FUNC_NAME: SomeClass::handleInputEvent
undefined4 FUN_00558260(int thisPtr, int param2, int *param3)

{
  int eventType;
  undefined4 result;
  int localArray [3];
  
  if (param2 != 0) {
    localArray[0] = 1;
    localArray[1] = 8;
    if (param3 == (int *)0x0) {
      // Call virtual function at offset +0x2c on the object at thisPtr+0x54
      // This likely gets default input parameters
      (**(code **)(*(int *)(thisPtr + 0x54) + 0x2c))(localArray);
      param3 = localArray;
    }
    eventType = *param3;
    // Check if event type is 2, 3, or 4 (likely button press/release/hold)
    if (((eventType == 3) || (eventType == 4)) || (eventType == 2)) {
      result = FUN_00558130(thisPtr, param2, param3);
      return result;
    }
  }
  return 0;
}