// FUNC_NAME: PriorityQueue::insertOrUpdate
void __thiscall PriorityQueue::insertOrUpdate(int this, int *param_2)
{
  int iVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined4 local_28;
  float local_24;
  undefined4 *local_18;
  undefined4 *local_10;
  undefined4 *local_c;
  float fStack_8;
  
  // Sort the heap array (bubble up? or just ensure ordering)
  FUN_0081ad00(*(int *)(this + 0x10), *(int *)(this + 0x10) + *(int *)(this + 0x14) * 0xc);
  
  // Get the index from param_2 (likely a key or ID)
  iVar1 = *(int *)(*(int *)(this + 0xc) + *(int *)(*(int *)(this + 0x24) + *param_2 * 0x1c) * 4);
  
  // Start iterating from the head of a linked list (stored at +0x18)
  local_18 = (undefined4 *)**(undefined4 **)(iVar1 + 0x18);
  
  while( true ) {
    puVar5 = local_18;
    local_10 = *(undefined4 **)(iVar1 + 0x18);
    if (iVar1 == 0) {
      FUN_00b97aea(); // likely assertion failure
    }
    if (puVar5 == local_10) break;
    
    local_28 = 0;
    if (iVar1 == 0) {
      FUN_00b97aea();
    }
    if (puVar5 == *(undefined4 **)(iVar1 + 0x18)) {
      FUN_00b97aea();
    }
    
    puVar5 = puVar5 + 2; // skip to data portion of node
    cVar3 = FUN_0081a4d0(puVar5, param_2, &local_28); // compare function
    if (cVar3 != '\0') {
      if (local_18 == *(undefined4 **)(iVar1 + 0x18)) {
        FUN_00b97aea();
      }
      fVar6 = (float10)FUN_0081b900(puVar5, param_2); // get priority value
      local_24 = (float)fVar6;
      if ((float10)0 <= fVar6) {
        if (local_18 == *(undefined4 **)(iVar1 + 0x18)) {
          FUN_00b97aea();
        }
        uVar2 = local_28;
        iVar4 = *(int *)(this + 0x18);
        fStack_8 = local_24;
        local_c = puVar5;
        
        // Resize heap array if needed
        if (*(int *)(this + 0x14) == iVar4) {
          if (iVar4 == 0) {
            iVar4 = 1;
          }
          else {
            iVar4 = iVar4 * 2;
          }
          FUN_00818f90(iVar4); // resize heap storage
        }
        
        puVar5 = (undefined4 *)(*(int *)(this + 0x10) + *(int *)(this + 0x14) * 0xc);
        *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;
        if (puVar5 != (undefined4 *)0x0) {
          *puVar5 = local_c;       // store pointer to node data
          puVar5[1] = fStack_8;    // store priority value
          puVar5[2] = uVar2;       // store some other data
        }
      }
    }
    if (local_18 == *(undefined4 **)(iVar1 + 0x18)) {
      FUN_00b97aea();
    }
    local_18 = (undefined4 *)*local_18; // move to next node in linked list
  }
  return;
}