// FUNC_NAME: SomeEngineClass::addReferenceToGlobalList
void FUN_005c9bb0(int param_1)

{
  int *ppvGlobalList;  // pointer to list pointer (list = array of pointers)
  
  // DAT_01206880 is a global variable; +0x14 is offset to a pointer
  // that points to current end of list (or next free slot)
  ppvGlobalList = (int *)(DAT_01206880 + 0x14);
  
  // Write pointer to vtable/function table (PTR_LAB_011261ac) at current list position
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_011261ac;
  
  // Advance list pointer by 4 (size of a pointer)
  *ppvGlobalList = *ppvGlobalList + 4;
  
  // Write the parameter (presumably an object/clip_ptr?) to the next slot
  *(undefined4 *)*ppvGlobalList = param_1;
  
  // Advance list pointer again
  *ppvGlobalList = *ppvGlobalList + 4;

  return;
}