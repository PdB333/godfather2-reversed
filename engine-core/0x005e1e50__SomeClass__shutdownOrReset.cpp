// FUNC_NAME: SomeClass::shutdownOrReset
undefined4 SomeClass::shutdownOrReset(void)

{
  int thisPtr;
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c;
  
  // Check if the flag at offset +0x1744 is set
  if (*(char *)(thisPtr + 0x1744) != '\0') {
    // Initialize a local structure (likely a vector or color)
    local_18 = 1;
    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    
    // Call function to process this structure
    FUN_005e2440(&local_18);
    
    // Loop 5 times calling another function
    iVar1 = 5;
    do {
      FUN_005e8610();
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    
    // Reset various fields at offsets +0x173c, +0x1738, +0x1740, +0x1744
    *(undefined4 *)(thisPtr + 0x173c) = 0;
    FUN_009c8f10(*(undefined4 *)(thisPtr + 0x1738));
    *(undefined4 *)(thisPtr + 0x1738) = 0;
    *(undefined4 *)(thisPtr + 0x1740) = 0;
    *(undefined1 *)(thisPtr + 0x1744) = 0;
  }
  return 1;
}