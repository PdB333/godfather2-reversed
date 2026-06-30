// FUNC_NAME: EARSObject::clearAllChildSlots

void EARSObject::clearAllChildSlots(void)
{
  int *arrayPtr;
  int iVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int temp;

  if (this == 0) {
    return;
  }
  // Pre-clear function (likely marks children for deletion)
  FUN_004598a0();
  // Check if object has the "children present" flags (bits 6 and 7)
  if (*(uint *)(this + 0x24) & 0xc0) {
    iVar1 = *(int *)(this + 0x98); // alternate parent pointer
    iVar3 = this;
    if ((int)(char)*(uint *)(this + 0x24) < 0) {
      iVar3 = iVar1; // use alternate if high bit set
    }
    // Clear child counts and pointers
    *(undefined2 *)(iVar3 + 0x44) = 0;
    *(undefined4 *)(iVar3 + 0x80) = 0;
    *(undefined4 *)(iVar3 + 0x84) = 0;
    *(undefined4 *)(this + 0x98) = 0;
    *(undefined4 *)(iVar1 + 0x98) = 0;
    // Clear flags bits 6 and 7
    *(uint *)(this + 0x24) &= 0xffffff3f;
    *(uint *)(iVar1 + 0x24) &= 0xffffff3f;
  }
  // Process two sets of arrays (each set contains two types)
  piVar2 = (int *)(this + 0x88); // base for first set
  temp = 2;
  do {
    // Free small objects (0x28 bytes each) from first array in the set
    uVar4 = 0;
    if (*(short *)(this + 0x44) != 0) {
      iVar1 = 0;
      do {
        FUN_00615ec0(piVar2[-2] + iVar1);
        uVar4 = uVar4 + 1;
        iVar1 = iVar1 + 0x28;
      } while (uVar4 < *(ushort *)(this + 0x44));
    }
    // Free larger objects (0x34 bytes each) from second array in the set
    uVar4 = 0;
    if (*(short *)(this + 0x46) != 0) {
      iVar1 = 0;
      do {
        FUN_00615fc0(*piVar2 + iVar1);
        uVar4 = uVar4 + 1;
        iVar1 = iVar1 + 0x34;
      } while (uVar4 < *(ushort *)(this + 0x46));
    }
    piVar2 = piVar2 + 1; // advance to next set
    temp = temp + -1;
  } while (temp != 0);
  // Free additional small objects from array at +0x94
  uVar4 = 0;
  if (*(int *)(this + 0x90) != 0) {
    iVar1 = 0;
    do {
      FUN_00615ec0(*(int *)(this + 0x94) + iVar1);
      uVar4 = uVar4 + 1;
      iVar1 = iVar1 + 0x28;
    } while (uVar4 < *(uint *)(this + 0x90));
  }
  // Free larger objects from array at +0x50 (stride 0xB0)
  uVar4 = 0;
  if (*(int *)(this + 0x34) != 0) {
    iVar1 = 0;
    do {
      iVar3 = *(int *)(this + 0x50) + iVar1;
      // Free secondary pointer at offset +0x0c within each element
      FUN_004d24f0(*(int *)(*(int *)(this + 0x50) + 0xc + iVar1));
      // If element has a sub-object flag, free that too
      if ((**(uint **)(iVar3 + 0x54) & 0x40000) != 0) {
        FUN_004d24f0(*(int *)(iVar3 + 0xc));
      }
      uVar4 = uVar4 + 1;
      iVar1 = iVar1 + 0xb0;
    } while (uVar4 < *(uint *)(this + 0x34));
  }
  // If we are in the main thread, add deletion to a pending list
  if (*(int *)(**(int **)(*(int *)(__readfsdword(0x2c)) + 0x34) + 0x34) == 1) {
    // Lock-free linked list enqueue
    void *newNode = PTR_DAT_01117bb0;
    while (newNode == 0) {
      PTR_DAT_01117bb0 = (void *)newNode;
      // Spin/yield
      FUN_00485280();
      newNode = (void *)PTR_DAT_01117bb0;
    }
    // Remove from free list
    PTR_DAT_01117bb0 = *(void **)(newNode + 12);
    *(void **)(newNode + 12) = 0;
    // Setup node vtable and data
    *(undefined4 *)newNode = &LAB_00485300; // vtable for deferred deletion
    *(int *)(newNode + 4) = DAT_01205870;   // function table
    *(int *)(newNode + 8) = this;           // object to delete
    // Enqueue at tail
    if (DAT_01117bc0 == 0) {
      DAT_01117bbc = newNode;
      DAT_01117bc0 = newNode;
      return;
    }
    *(void **)((int)DAT_01117bc0 + 12) = newNode;
    DAT_01117bc0 = newNode;
    return;
  }
  // If not main thread, call virtual function directly (unsafe)
  (**(code **)(*DAT_01205870 + 4))();
}