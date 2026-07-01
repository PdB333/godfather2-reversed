// FUNC_NAME: PriorityQueue::updateInsert
void __thiscall PriorityQueue::updateInsert(int *this,int *node)
{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  float10 fVar8;
  uint uStack_3c;
  uint uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  // Get the object pointer from node (node is a linked list node at offset +0x48 from object)
  if (*node == 0) {
    piVar7 = (int *)0x0;
  }
  else {
    piVar7 = (int *)(*node + -0x48); // object at -0x48 from node->next
  }
  // Call virtual function at vtable+0x24 (getPosition?)
  (**(code **)(*piVar7 + 0x24))(&local_20);
  
  if (*node == 0) {
    piVar7 = (int *)0x0;
  }
  else {
    piVar7 = (int *)(*node + -0x48);
  }
  // Call virtual function at vtable+0x28 (getPriority?)
  fVar8 = (float10)(**(code **)(*piVar7 + 0x28))();
  
  // Initialize stack-based temporary
  FUN_004262f0(0); // clear some state
  
  uStack_34 = uStack_24;
  uStack_30 = local_20;
  uStack_2c = uStack_1c;
  fStack_28 = (float)fVar8;
  
  // Check if node should be updated in the queue
  iVar4 = FUN_004bdae0(&uStack_34);
  if (iVar4 != 2) {
    bVar1 = false;
    piVar7 = (int *)0x0;
    bVar2 = false;
    uStack_38 = 0;
    uStack_3c = 0;
    do {
      if (bVar2) {
        return;
      }
      if (3 < uStack_3c) goto LAB_0089e7e3;
      iVar4 = *this;
      if (iVar4 == 0) {
        iVar6 = 0;
      }
      else {
        iVar6 = iVar4 + -0x48;
      }
      if (*node == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = *node + -0x48;
      }
      if (iVar6 == iVar5) {
        bVar2 = true; // found node in queue, nothing to update
      }
      else {
        if ((iVar4 == 0) || (iVar4 == 0x48)) {
          bVar1 = true; // reached end of list
          uVar3 = uStack_38;
        }
        else {
          uVar3 = this[2];
          if ((uint)this[2] <= uStack_38) goto LAB_0089e7d0;
        }
        uStack_38 = uVar3;
        piVar7 = this; // current node in iteration
      }
LAB_0089e7d0:
      uStack_3c = uStack_3c + 1;
      this = this + 3; // advance to next node (each node is 12 bytes? or 3 ints)
    } while (!bVar1);
    
    if (!bVar2) {
LAB_0089e7e3:
      if (piVar7 != (int *)0x0) {
        if (piVar7 != node) {
          iVar4 = *node;
          if (*piVar7 != iVar4) {
            if (*piVar7 != 0) {
              FUN_004daf90(piVar7); // remove old next pointer
            }
            *piVar7 = iVar4; // reassign linked list next
            if (iVar4 != 0) {
              piVar7[1] = *(int *)(iVar4 + 4); // update prev pointer
              *(int **)(iVar4 + 4) = piVar7; // fix back pointer
            }
          }
        }
        piVar7[2] = 0; // mark as updated
      }
    }
  }
  return;
}