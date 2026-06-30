// FUNC_NAME: SomeClass::initializeSomething
void FUN_005d5d40(void)
{
  int iVar1;
  int *piVar2;
  
  // Calculate offset into some data structure (0x1c = 28 bytes per entry)
  iVar1 = DAT_012056bc * 0x1c;
  
  // Get pointer to vtable or function table at global + 0x14
  piVar2 = (int *)(DAT_01206880 + 0x14);
  
  // Set vtable pointer to a known function table
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_FUN_01126cf8;
  
  // Increment the pointer (likely advancing through a vtable array)
  *piVar2 = *piVar2 + 4;
  
  // Call initialization function with parameters:
  // - 4: some type/ID
  // - CONCAT44(iVar1, &DAT_0119eac0): combined index and data pointer
  // - 0x10: size (16 bytes)
  // - 0x1c: stride (28 bytes, matching the multiplication factor)
  FUN_005d7490(4, CONCAT44(iVar1, &DAT_0119eac0), 0x10, 0x1c);
  
  return;
}