// FUNC_NAME: EARSObject::copyConstructorOrAssignmentOperator
uint* EARSObject::copyConstructorOrAssignmentOperator(uint* thisPtr)
{
  uint* puVar1;
  uint in_EAX;
  uint* puVar2;
  uint uVar3;
  int iVar4;
  undefined1* local_14;
  undefined1 local_10[16];

  iVar4 = (int)thisPtr;
  if (thisPtr != (uint*)0x0) {
    // Assignment operator path: thisPtr is existing object
    thisPtr = (uint*)0x0;
    if (in_EAX != 0) {
      // Allocate memory for the array of elements (each 0x20 bytes)
      uVar3 = -(uint)((int)((ulonglong)in_EAX * 0x20 >> 0x20) != 0) |
              (uint)((ulonglong)in_EAX * 0x20);
      puVar2 = (uint*)FUN_009c8e50(-(uint)(0xfffffffb < uVar3) | uVar3 + 4);
      if (puVar2 == (uint*)0x0) {
        thisPtr = (uint*)0x0;
      }
      else {
        thisPtr = puVar2 + 1;
        *puVar2 = in_EAX; // Store element count at offset -4
        _vector_constructor_iterator_(thisPtr, 0x20, in_EAX, (_func_void_ptr_void_ptr*)&LAB_0059cf80);
      }
      // Copy elements from source (iVar4) to destination (thisPtr)
      uVar3 = (-1 < (int)in_EAX) - 1 & in_EAX;
      puVar2 = thisPtr;
      while (uVar3 != 0) {
        uVar3 = uVar3 - 1;
        FUN_005a0a00(iVar4); // Copy element at source offset
        FUN_005a1060();      // Possibly increment or process
        if ((local_14 != local_10) && (local_14 != (undefined1*)0x0)) {
          (*DAT_0119caf4)(local_14); // Free temporary buffer if allocated
        }
        puVar1 = (uint*)(iVar4 + 0x1c);
        iVar4 = iVar4 + 0x20;
        puVar2[7] = *puVar1; // Copy last dword of element (offset 0x1c)
        puVar2 = puVar2 + 8;
      }
    }
    // Destroy old contents of thisPtr (if any)
    if (iVar4 != 0) {
      FUN_0040cd70(iVar4, 0x20, *(undefined4*)(iVar4 + -4), &LAB_0059cfc0);
      FUN_009c8eb0(iVar4 + -4); // Free the allocation
    }
    return thisPtr;
  }
  // Constructor path: thisPtr is null, allocate new object
  uVar3 = -(uint)((int)((ulonglong)in_EAX * 0x20 >> 0x20) != 0) |
          (uint)((ulonglong)in_EAX * 0x20);
  puVar2 = (uint*)FUN_009c8e50(-(uint)(0xfffffffb < uVar3) | uVar3 + 4);
  if (puVar2 != (uint*)0x0) {
    *puVar2 = in_EAX;
    _vector_constructor_iterator_(puVar2 + 1, 0x20, in_EAX, (_func_void_ptr_void_ptr*)&LAB_0059cf80);
    return puVar2 + 1;
  }
  return (uint*)0x0;
}