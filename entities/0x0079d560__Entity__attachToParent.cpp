// FUNC_NAME: Entity::attachToParent
void __thiscall Entity::attachToParent(Entity *this, Entity *parent)
{
  int *listHeadPtr;
  int nodeBase;
  
  // Check if the "attached" flag (bit 10 of field at +0x8DC) is clear
  if (((uint)this->flags1 >> 10 & 1) == 0) {
    // First list insertion (child list)
    listHeadPtr = &this->childListHead; // +0x1d3*4 = +0x74C
    if (parent != 0) {
      nodeBase = (int)parent + 0x48; // parent node structure at +0x48
    } else {
      nodeBase = 0;
    }
    if (*listHeadPtr != nodeBase) {
      if (*listHeadPtr != 0) {
        listRemove(listHeadPtr);
      }
      *listHeadPtr = nodeBase;
      if (nodeBase != 0) {
        this->childListOldNext = *(int *)(nodeBase + 4); // save node's original next
        *(int **)(nodeBase + 4) = listHeadPtr; // point node's next back to head pointer
      }
    }
    // Second list insertion (another list, e.g., sibling list)
    listHeadPtr = &this->siblingListHead; // +0x92d*4 = +0x24B4
    if (parent != 0) {
      nodeBase = (int)parent + 0x48;
    } else {
      nodeBase = 0;
    }
    if (*listHeadPtr != nodeBase) {
      if (*listHeadPtr != 0) {
        listRemove(listHeadPtr);
      }
      *listHeadPtr = nodeBase;
      if (nodeBase != 0) {
        this->siblingListOldNext = *(int *)(nodeBase + 4);
        *(int **)(nodeBase + 4) = listHeadPtr;
      }
    }
  } else {
    // Flag set: call pre-attach callback (vtable+0x260)
    (this->vtable->preAttach)(this);
    // Then perform same list insertions (duplicated code, likely a bug in decompilation or intentional)
    listHeadPtr = &this->childListHead;
    if (parent != 0) {
      nodeBase = (int)parent + 0x48;
    } else {
      nodeBase = 0;
    }
    if (*listHeadPtr != nodeBase) {
      if (*listHeadPtr != 0) {
        listRemove(listHeadPtr);
      }
      *listHeadPtr = nodeBase;
      if (nodeBase != 0) {
        this->childListOldNext = *(int *)(nodeBase + 4);
        *(int **)(nodeBase + 4) = listHeadPtr;
      }
    }
    listHeadPtr = &this->siblingListHead;
    if (parent != 0) {
      nodeBase = (int)parent + 0x48;
    } else {
      nodeBase = 0;
    }
    if (*listHeadPtr != nodeBase) {
      if (*listHeadPtr != 0) {
        listRemove(listHeadPtr);
      }
      *listHeadPtr = nodeBase;
      if (nodeBase != 0) {
        this->siblingListOldNext = *(int *)(nodeBase + 4);
        *(int **)(nodeBase + 4) = listHeadPtr;
      }
    }
    // Post-attach callback (vtable+0x25c)
    (this->vtable->postAttach)(this);
  }
  // Set rebuild flag (bit 9) on field at +0x24A0
  this->transformDirtyFlags |= 0x200;
  // Notify spatial node (at +0x58) to update (vtable+0x28)
  (*(this->spatialNode)->vtable->update)(this->spatialNode);
}