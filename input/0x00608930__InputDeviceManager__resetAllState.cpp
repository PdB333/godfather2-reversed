// FUNC_NAME: InputDeviceManager::resetAllState
void InputDeviceManager::resetAllState(void)
{
  InputDeviceManager *deviceMgr;
  int i;
  InputDeviceSlot *slotPtr; // out param for slot object
  int *intPtr; // out param for something
  InputDeviceSlot *slotPtr2; // out param for slot object 2
  InputDeviceSlot *slotPtr3; // out param for slot object 3
  int localInt; // used as out param for 0x69 call
  int *tempIntPtr; // used for release checks

  deviceMgr = gInputDeviceManager; // DAT_01205750
  if (gInputDeviceManagerInitFlag != '\0') { // DAT_01205758
    // Local stack array for temporary storage
    tempStackArray[0] = 0; // puStack_28, local_1c[0] = 0

    // Save original deviceMgr pointer for later
    savedDeviceMgr = gInputDeviceManager; // ppuStack_2c = DAT_01205750

    // Clear the init flag
    gInputDeviceManagerInitFlag = '\0'; // DAT_01205758 = 0

    // Call method at vtable offset 0x6c (likely init or resetState)
    (*(code *)((*deviceMgr)[0x6c]))();

    // Call method at vtable offset 0x6b (likely prepare or beginReset)
    (*(code *)((*deviceMgr)[0x6b]))();

    // Release previously saved deviceMgr if non-null (vtable[2] is release)
    if (savedDeviceMgr != NULL) {
      (*(code *)((*savedDeviceMgr)[2]))(); // release
    }

    // Call method at vtable offset 0x5d with tempStackArray (likely something like getDeviceInfo)
    (*(code *)((*deviceMgr)[0x5d]))(deviceMgr, &tempStackArray);

    // Call method at vtable offset 0x5c (likely clearDeviceInfo or endGet)
    (*(code *)((*deviceMgr)[0x5c]))(deviceMgr);

    // Release tempStackArray if non-null
    if (tempStackArray[0] != NULL) {
      (*(code *)((*tempStackArray[0])[2]))(tempStackArray[0]);
    }

    // Loop over 16 controller slots
    i = 0;
    do {
      slotPtr = NULL;
      // Get slot object for index i (vtable[0x40])
      (*(code *)((*deviceMgr)[0x40]))(deviceMgr, i, &slotPtr);
      // Set slot object to NULL (vtable[0x41])
      (*(code *)((*deviceMgr)[0x41]))(deviceMgr, i, 0);
      if (slotPtr != NULL) {
        (*(code *)((*slotPtr)[2]))(slotPtr); // release
      }
      i = i + 1;
    } while (i < 16);

    // Call vtable[0x69] with localInt (get some state)
    (*(code *)((*deviceMgr)[0x69]))(deviceMgr, &localInt);
    // Call vtable[0x68] with 0 (set some state)
    (*(code *)((*deviceMgr)[0x68]))(deviceMgr, 0);

    // Release tempIntPtr if non-null
    if (tempIntPtr != NULL) {
      (*(code *)(*(tempIntPtr + 8)))(tempIntPtr); // probably a different release pattern
    }

    // Another loop over 16 slots, getting three out params
    i = 0;
    do {
      slotPtr = NULL;
      slotPtr2 = NULL;
      slotPtr3 = NULL;
      // Get triple slot objects (vtable[0x65])
      (*(code *)((*deviceMgr)[0x65]))(deviceMgr, i, &slotPtr3, &slotPtr2, &slotPtr);
      // Clear triple (vtable[100])
      (*(code *)((*deviceMgr)[100]))(deviceMgr, i, 0, 0, 0);
      if (slotPtr3 != NULL) {
        (*(code *)((*slotPtr3)[2]))(slotPtr3); // release
      }
      i = i + 1;
    } while (i < 16);

    // Get another object (vtable[0x58])
    (*(code *)((*deviceMgr)[0x58]))(deviceMgr, &slotPtr2);
    if (slotPtr3 != NULL) {
      (*(code *)((*slotPtr3)[2]))(slotPtr3); // release
    }

    // Clear global state flags to 0
    gSomeState1 = 0; // DAT_01205830
    gSomeState2 = 0; // DAT_01205834
    gSomeState3 = 0; // DAT_01205838
    gSomeState4 = 0; // DAT_0120583c

    // Clear input state arrays (256 bytes, 4096 bytes, 4096 bytes)
    memset(&gButtonStateArray, -1, 0x100);    // DAT_011da7f0
    memset(&gAxisStateArray1, -1, 0x1000);   // DAT_011d97f0
    memset(&gAxisStateArray2, -1, 0x1000);   // DAT_011ea8f0

    // Final initialization step (vtable[0x2a])
    (*(code *)((*deviceMgr)[0x2a]))(deviceMgr);
  }
  return;
}