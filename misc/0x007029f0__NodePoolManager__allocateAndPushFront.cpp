// FUNC_NAME: NodePoolManager::allocateAndPushFront
void __fastcall NodePoolManager::allocateAndPushFront(int *this)
{
  int *pendingCount;
  int *piVar4;
  int iVar2;
  undefined4 uVar3;
  int *newNode;
  int secondaryObj;
  int aiStack_60[3];
  float timestamp;
  char tempBuffer[76];
  
  pendingCount = this + 0x138;
  // Check if any pending count is non-zero and if we are allowed to allocate
  if (((((*pendingCount != 0) || (this[0x139] != 0)) || (this[0x13a] != 0)) || (this[0x13b] != 0))
      && (((*(byte *)(this + 0xb6) & 1) == 0 || (this[0x13c] == 0)))) {
    
    // Initialize temp buffer (possibly key or descriptor)
    FUN_00701060(tempBuffer);
    
    aiStack_60[1] = 0;
    aiStack_60[2] = this[0x13f];          // node type
    timestamp = (float)this[0x140] + _DAT_00d5780c; // adjust with global time offset
    
    if ((*(byte *)(this + 0xb6) & 1) == 0) {
      // Standard allocation
      secondaryObj = 0;
      uVar3 = (**(code **)(*this + 0x58))(0, &secondaryObj);
      newNode = (int *)createNode(aiStack_60, pendingCount, tempBuffer, uVar3);
      
      this[0x13c] = (int)newNode;
      if (this[0x13c] != 0) {
        *(int *)(this[0x13c] + 8) = 0; // clear back pointer in old head (should be redundant)
        this[0x13c] = 0;                   // reset head
      }
      iVar2 = *newNode;
      this[0x13c] = iVar2;                // new node becomes head
      if (iVar2 != 0) {
        *(int **)(iVar2 + 8) = &this[0x13c]; // store backpointer to head ptr
      }
      *newNode = 0;                      // clear next pointer? Actually *newNode was assigned earlier, but here it's cleared
    }
    else {
      // Allocation with secondary object
      uVar3 = (**(code **)(*this + 0x58))(0, this, 0xffffffff, aiStack_60 + 1);
      newNode = (int *)createNodeWithSecondary(&secondaryObj, pendingCount, tempBuffer, uVar3);
      
      this[0x13c] = (int)newNode;
      if (this[0x13c] != 0) {
        *(int *)(this[0x13c] + 8) = 0;
        this[0x13c] = 0;
      }
      iVar2 = *newNode;
      this[0x13c] = iVar2;
      aiStack_60[0] = secondaryObj;
      if (iVar2 != 0) {
        *(int **)(iVar2 + 8) = &this[0x13c];
      }
      *newNode = 0;
      if (aiStack_60[0] != 0) {
        *(int *)(aiStack_60[0] + 8) = 0; // clear secondary object's backpointer if any
      }
    }
  }
}