// FUNC_NAME: EARSObject::release
void EARSObject::release(void)
{
  int iVar1;
  
  // Call base class release or decrement ref count
  FUN_005a1f20();
  
  // Check if object state is 3 (loaded) or 4 (active)
  if ((*(int *)(this + 0x20) == 3) || (*(int *)(this + 0x20) == 4)) {
    // Call destructor for data at +0x24
    FUN_005a5650(*(undefined4 *)(this + 0x24));
    // Call global function pointer for cleanup at +0x2c
    (*DAT_0119cb14)(*(undefined4 *)(this + 0x2c));
  }
  
  // Check if next pointer (+0xc) is valid and not pointing to self (+0x10)
  iVar1 = *(int *)(this + 0xc);
  if ((iVar1 != this + 0x10) && (iVar1 != 0)) {
    // Call global function pointer to free memory
    (*DAT_0119caf4)(iVar1);
  }
  
  return;
}