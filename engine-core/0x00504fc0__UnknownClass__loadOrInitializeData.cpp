// FUNC_NAME: UnknownClass::loadOrInitializeData
void __thiscall FUN_00504fc0(int this, int *param2)
{
  undefined4 *vtablePtr;
  float *fltPtr;
  int *intPtr;
  undefined4 undef4_1;
  undefined4 undef4_2;
  uint flags;
  int someInt1;
  int someInt2;
  undefined4 *ediBackup;
  int fsOffset;
  
  FUN_00533cc0();
  *ediBackup = &PTR_FUN_00e37f58; // Set vtable pointer
  if (*(char *)(this + 0xd) == '\0') { // Check some flag at offset +0xd
    ediBackup[10] = 0;
    undef4_1 = DAT_00e2b1a4; // Some constant
    ediBackup[0xb] = DAT_00e2b1a4;
    ediBackup[0xc] = undef4_1;
    ediBackup[9] = param2; // Store param2 pointer
    **(uint **)(this + 4) = **(uint **)(this + 4) | 0x100000; // Set flag on object at +0x4
    someInt2 = **(int **)(fsOffset + 0x2c); // Get value from FS segment
    vtablePtr = (undefined4 *)(ediBackup[4] + 0x10 + *(int *)(someInt2 + 8)); // Calculate address
    *vtablePtr = undef4_1; // Initialize vtable-like structure with constants
    vtablePtr[1] = 0;
    vtablePtr[2] = 0;
    vtablePtr[3] = 0;
    vtablePtr[4] = 0;
    vtablePtr[5] = undef4_1;
    vtablePtr[6] = 0;
    vtablePtr[7] = 0;
    vtablePtr[8] = 0;
    vtablePtr[9] = 0;
    vtablePtr[10] = undef4_1;
    vtablePtr[0xb] = 0;
    if ((param2[5] & 2U) == 0) { // Check flags at param2+0x14
      if ((param2[5] & 4U) != 0) { // Check another flag
        someInt1 = ediBackup[4];
        someInt2 = *(int *)(someInt2 + 8);
        *(int *)(someInt1 + 0x40 + someInt2) = param2[0xc]; // Copy values from param2 to target
        someInt2 = someInt1 + 0x40 + someInt2;
        *(int *)(someInt2 + 4) = param2[0xd];
        *(int *)(someInt2 + 8) = param2[0xe];
      }
    }
    else { // If bit 1 set in flags, add float values instead
      fltPtr = (float *)(ediBackup[4] + 0x40 + *(int *)(someInt2 + 8));
      *fltPtr = (float)param2[0xc] + *fltPtr;
      fltPtr[1] = (float)param2[0xd] + fltPtr[1];
      fltPtr[2] = (float)param2[0xe] + fltPtr[2];
    }
    FUN_004ebb40(); // Call some initialization
    flags = 0;
    if ((*param2 != 0 || param2[1] != 0) || (param2[2] != 0 || param2[3] != 0)) { // Check if first 4 ints non-zero
      flags = FUN_004e9270(); // Get some resource/index
      if (((flags != 0) &&
          (((flags != 0xffffffff && (flags < 0x1000)) && (flags * 0x38 != -0x11a0f28)))) &&
         (intPtr = *(int **)(&DAT_011a0f38 + flags * 0x38), intPtr != (int *)0x0)) {
        *intPtr = *intPtr + 1; // Increment reference counter
      }
    }
    undef4_2 = ediBackup[1]; // Extract vtable or pointer
    vtablePtr = (undefined4 *)param2; // Overwrite - likely bug, param2 used differently
    someInt1 = DAT_0119478c + -1;
    someInt2 = DAT_0119478c + 2;
    if (someInt1 < 0) {
      someInt1 = 0x13; // Wrap around
    }
    else if (0x13 < someInt2) {
      someInt2 = DAT_0119478c + -0x12; // Another wrap
    }
    (&DAT_01194790)[someInt1] = (&DAT_01194790)[someInt1] + (&DAT_01194790)[someInt2]; // Add two values in array
    DAT_0119478c = someInt1; // Update index
    FUN_00504d40(ediBackup, *(undefined4 *)(ediBackup[1] + 0x10), CONCAT44(undef4_2, param2),
                 CONCAT44((&DAT_01194790)[someInt1], vtablePtr), flags, ediBackup[4], ediBackup[5]); // Call final function
  }
  return;
}