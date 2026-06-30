// FUNC_NAME: SomeManagerClass::resetOrDestructor
void __thiscall SomeManagerClass::resetOrDestructor(void)
{
  // Set vtable pointer (PTR_LAB_00e42f48 is the vtable)
  *(undefined4 **)this = &PTR_LAB_00e42f48;
  
  // Call first sub-function (likely a partial reset/cleanup)
  FUN_00652df0();
  
  // If pointer at this + 0x1FC (0x7F * 4) is non-null, call another cleanup
  if (this[0x7f] != 0) {
    FUN_00650de0();
  }
  
  // Call another cleanup function
  FUN_00650d80();
  
  // Free resources: pointers at this + 0x210, 0x218, 0x214, 0x1FC
  // (0x84, 0x86, 0x85, 0x7F * 4 respectively)
  FUN_009c8f10(this[0x84]);  // free/delete pointer at +0x210
  FUN_009c8f10(this[0x86]);  // free/delete pointer at +0x218
  FUN_009c8f10(this[0x85]);  // free/delete pointer at +0x214
  FUN_009c8f10(this[0x7f]);  // free/delete pointer at +0x1FC
  
  // LinkedList removal logic: pointer at this + 0x21C (0x87*4)
  if (this[0x87] != 0) {
    // Adjust prev/next pointers of adjacent nodes
    if (this[0x88] == 0) {  // null previous pointer
      *(undefined4 *)(this[0x87] + 4) = this[0x89];  // node->next = newPrev
    }
    else {
      *(undefined4 *)(this[0x88] + 8) = this[0x89];  // prev->next = newPrev
    }
    
    if (this[0x89] != 0) {
      *(undefined4 *)(this[0x89] + 4) = this[0x88];  // next->prev = oldPrev
    }
  }
  
  // Final cleanup call
  FUN_0064e060();
  
  return;
}