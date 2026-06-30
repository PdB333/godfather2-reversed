// FUNC_NAME: StringTable::removeEntry
void __thiscall StringTable::removeEntry(int this, byte *key)
{
  byte bVar1;
  int *piVar2;
  byte *pbVar3;
  byte *pbVar4;
  int iVar5;
  int *piVar6;
  bool bVar7;
  
  piVar6 = (int *)**(undefined4 **)(this + 0x24); // +0x24: hash table bucket array
  do {
    if (piVar6 == *(int **)(this + 0x24)) { // end of bucket list
      return;
    }
    if (piVar6 == *(int **)(this + 0x24)) {
      FUN_00b97aea(); // likely assertion or error handler
    }
    piVar2 = (int *)piVar6[2]; // +0x08: entry data pointer
    pbVar3 = (byte *)*piVar2; // +0x00: string pointer in entry
    pbVar4 = key;
    if (pbVar3 == (byte *)0x0) {
      pbVar3 = &DAT_0120546e; // empty string fallback
    }
    // String comparison loop (2-byte aligned)
    do {
      bVar1 = *pbVar4;
      bVar7 = bVar1 < *pbVar3;
      if (bVar1 != *pbVar3) {
LAB_004ce427:
        iVar5 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_004ce42c;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar4[1];
      bVar7 = bVar1 < pbVar3[1];
      if (bVar1 != pbVar3[1]) goto LAB_004ce427;
      pbVar3 = pbVar3 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar5 = 0;
LAB_004ce42c:
    if (iVar5 == 0) { // match found
      if ((piVar6 != *(int **)(this + 0x24)) ||
         (FUN_00b97aea(), piVar6 != *(int **)(this + 0x24))) {
        // Remove node from linked list
        *(int *)piVar6[1] = *piVar6; // prev->next = next
        *(int *)(*piVar6 + 4) = piVar6[1]; // next->prev = prev
        (**(code **)(**(int **)(this + 0xc) + 4))(piVar6, 0xc); // free node (size 0xC)
        *(int *)(this + 0x28) = *(int *)(this + 0x28) + -1; // decrement count
      }
      // Free entry data
      FUN_004086d0(piVar2 + 8); // likely destructor for some sub-object
      FUN_00408310(piVar2 + 8); // likely free memory
      if (piVar2[4] != 0) { // +0x10: destructor callback
        (*(code *)piVar2[7])(piVar2[4]); // +0x1C: call destructor
      }
      if (*piVar2 != 0) { // +0x00: string pointer
        (*(code *)piVar2[3])(*piVar2); // +0x0C: free string
      }
      iVar5 = *(int *)(this + 0x2c); // +0x2C: some flag
      (*DAT_012059e0)(piVar2); // free entry struct
      if (iVar5 == 0) {
        return;
      }
      piVar6 = (int *)(*(int *)(iVar5 + 0x10) + 0x24); // adjust iterator
      *piVar6 = *piVar6 + -0x28; // decrement some counter
      return;
    }
    if (piVar6 == *(int **)(this + 0x24)) {
      FUN_00b97aea(); // assertion
    }
    piVar6 = (int *)*piVar6; // move to next node
  } while( true );
}