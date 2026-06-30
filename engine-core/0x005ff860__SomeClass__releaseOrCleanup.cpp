// FUNC_NAME: SomeClass::releaseOrCleanup
void __fastcall SomeClass::releaseOrCleanup(undefined4 *this)
{
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Check if two pointers at offsets +0x7C and +0x84 are non-null
  if ((this[0x1f] != 0) && (this[0x21] != 0)) {
    // Save original values before unlinking
    local_c = *this;                          // +0x00
    local_18 = this[0x22];                    // +0x88
    local_8 = this[1];                        // +0x04
    local_4 = this[2];                        // +0x08
    local_14 = 0;
    if (local_18 != 0) {
      local_14 = *(undefined4 *)(local_18 + 4); // Save next pointer
      *(int **)(local_18 + 4) = &local_18;      // Unlink from list
    }
    local_10 = this[0x24];                    // +0x90
    local_24 = this[0x1f];                    // +0x7C
    local_20 = 0;
    if (local_24 != 0) {
      local_20 = *(undefined4 *)(local_24 + 4); // Save next pointer
      *(int **)(local_24 + 4) = &local_24;      // Unlink from list
    }
    local_1c = this[0x21];                    // +0x84
    // Call cleanup functions with the saved data
    FUN_00600a40(&local_24, &local_c, 0, 0, 0);
    FUN_005f7ba0(&local_18);
    FUN_005f5bb0();
    FUN_005f5bb0();
  }
  return;
}