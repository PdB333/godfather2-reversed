// FUNC_NAME: ArrayContainer::resize
void __thiscall ArrayContainer::resize(uint newCapacity)
{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;

  // Only resize if new capacity is larger than current
  if ((uint)this[2] < newCapacity) {
    // Allocate new array: each element is 8 bytes (data + next pointer)
    piVar5 = (int *)FUN_009c8e80(newCapacity * 8);
    if (this[0] != 0) {
      uVar7 = 0;
      piVar6 = piVar5;
      if (this[1] != 0) {
        do {
          // Pointer to old slot
          piVar1 = (int *)(this[0] + uVar7 * 8);
          if (piVar6 != (int *)0x0) {
            // Copy data from old slot
            iVar2 = *piVar1;
            *piVar6 = iVar2;
            // Clear next pointer in new slot
            piVar6[1] = 0;
            if (iVar2 != 0) {
              // Update the 'next' field of the data object to point to new slot
              // The data object stores a 'next' pointer at offset +0x04
              piVar6[1] = *(int *)(iVar2 + 4);
              *(int **)(iVar2 + 4) = piVar6;
            }
          }
          // Now adjust the linked list to remove the old slot
          iVar2 = *piVar1;
          if (iVar2 != 0) {
            // Get the next pointer from the data object (this is the head of the list linking slots)
            piVar3 = *(int **)(iVar2 + 4);
            if (piVar3 == piVar1) {
              // If the data object's next points directly to the old slot,
              // update it to the old slot's next (which is now part of new slot's chain)
              *(int *)(iVar2 + 4) = piVar1[1];
            }
            else {
              // Traverse the list to find the predecessor of the old slot
              piVar4 = (int *)piVar3[1];
              while (piVar4 != piVar1) {
                piVar3 = (int *)piVar3[1];
                piVar4 = (int *)piVar3[1];
              }
              // Update predecessor's next to skip the old slot
              piVar3[1] = piVar1[1];
            }
          }
          uVar7 = uVar7 + 1;
          piVar6 = piVar6 + 2;
        } while (uVar7 < (uint)this[1]);
      }
      // Free old array
      FUN_009c8f10(this[0]);
    }
    // Point to new array and update capacity
    this[0] = (int)piVar5;
    this[2] = newCapacity;
  }
}