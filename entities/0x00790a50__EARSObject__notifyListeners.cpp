// FUNC_NAME: EARSObject::notifyListeners
void __fastcall EARSObject::notifyListeners(int this)
{
  int iVar1;
  undefined4 *puVar2;
  
  // Check if object is not destroyed (bit 0x19 of flags at +0x5c) and has listeners (+0xac)
  if (((*(uint *)(this + 0x5c) >> 0x19 & 1) == 0) && (*(int *)(this + 0xac) != 0)) {
    // Set bit 0x19 (0x2000000) to mark notification in progress
    *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) | 0x2000000;
    
    // Iterate through listener array at *(this+0xac)
    // Array count stored at offset +4 from the listener list pointer
    iVar1 = *(int *)(*(int *)(this + 0xac) + 4);
    while (iVar1 = iVar1 + -1, -1 < iVar1) {
      // Each listener is a pointer at *(listArray + index*4)
      puVar2 = *(undefined4 **)(**(int **)(this + 0xac) + iVar1 * 4);
      if (puVar2 != (undefined4 *)0x0) {
        // Call virtual function at vtable[0] on listener with 'this' as parameter
        (**(code **)*puVar2)(this);
      }
    }
    // Call cleanup/notification done handler
    FUN_007909d0();
    return;
  }
  return;
}