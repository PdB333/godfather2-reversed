// FUNC_NAME: Vector32::insertRange

// Function at 0x005a3480
// Based on decompiled x86 code from Godfather 2 (2008)
// Reconstructed from Ghidra export
// This function inserts a range of 32-byte elements into a dynamic array container.
// The container structure (param_1) layout:
//   +0x00: size (number of elements)
//   +0x04: capacity
//   +0x08: data pointer (void* to element array)
// Element size: 0x20 (32 bytes)
// The range to insert is defined by param_2 and param_3 (pointers to start and end integer offsets?).
// Actually, *param_2 and *param_3 are treated as indices (or byte offsets?) and the number of elements
// is (*param_3 - *param_2) >> 5.
// The 'this' pointer (in_EAX) points to an object that maintains an internal pointer to the buffer
// (maybe an iterator or a subrange).

void __thiscall Vector32::insertRange(int *param_1, int *param_2, int *param_3)
{
  int iVar1; // current size * 0x20 + data pointer
  int iVar2; // pointer to element at insertion point after reallocation?
  int *in_EAX; // this pointer (passed in ECX)
  int iVar3; // number of 32-byte elements to insert
  int iVar4; // internal pointer to the insertion position (from this->member)
  undefined4 local_24; // stack placeholder for scope guard
  undefined4 local_20;
  undefined8 *local_1c; // pointer to local_18?
  undefined8 local_18; // 8-byte stack buffer used as temporary
  undefined8 local_10;
  undefined4 local_8;

  // Calculate number of elements: (endOffset - startOffset) / 32
  iVar3 = (*param_3 - *param_2) >> 5;
  FUN_0059c140(-1 < iVar3); // assert that iVar3 >= 0

  if (0 < iVar3) {
    iVar1 = *param_1; // current size (element count)
    iVar4 = *in_EAX; // this->someInternalPointer (pointer to an element in the buffer)

    // Check if capacity is sufficient for insertion of iVar3 elements
    if (param_1[1] <= iVar1 + iVar3) {
      iVar2 = param_1[2]; // current data pointer
      FUN_005a36c0(); // grow buffer (reallocation)
      // Recalc iVar4 after reallocation:
      // iVar4 - iVar2 gives byte offset of the insertion point in old buffer,
      // then /32 gives index, *32 gives new byte offset, + new data pointer.
      iVar4 = (iVar4 - iVar2 >> 5) * 0x20 + param_1[2];
    }

    iVar2 = *param_1 * 0x20 + param_1[2]; // pointer to end of existing data

    if (iVar4 == iVar2) {
      // Insert at end: construct new element directly from source
      FUN_005a3830(*param_3);
    } else {
      // Insert in middle: move elements and then construct
      FUN_005a3890(iVar4, iVar2);
      FUN_005a3830(*param_3, iVar4);
    }

    // Scope guard / temporary lifetime management (likely unused here)
    local_1c = &local_18;
    local_24 = 0;
    local_20 = 0;
    local_18 = 0;
    local_10 = 0;
    local_8 = 0;
    FUN_005a1000(&local_24);
    if ((local_1c != &local_18) && (local_1c != (undefined8 *)0x0)) {
      (*DAT_0119caf4)(local_1c); // deallocator if needed
    }

    // Update size
    *param_1 = iVar1 + iVar3;
  }
  return;
}