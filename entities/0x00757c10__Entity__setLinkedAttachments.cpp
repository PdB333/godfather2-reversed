// FUNC_NAME: Entity::setLinkedAttachments

void __thiscall Entity::setLinkedAttachments(int *this, int *link1Node, int *link2Node, char enableLink1)

{
  int *oldNodePtr;
  int newNodeData;
  
  // Validate input nodes - both must be non-null and have non-zero first fields
  if ((((*link1Node != 0) && (link1Node[2] != 0)) && (*link2Node != 0)) && (link2Node[2] != 0)) {
    // Update flags at offset +0xA8
    if (enableLink1 == '\0') {
      // Enable both links (set bits 0x1000 and 0x2000)
      *(uint *)(this + 0xa8) = *(uint *)(this + 0xa8) | 0x1000;
      *(uint *)(this + 0xa8) = *(uint *)(this + 0xa8) | 0x2000;
    }
    else {
      // Disable link1 (clear bit 0x1000) but keep link2 enabled (set bit 0x2000)
      *(uint *)(this + 0xa8) = *(uint *)(this + 0xa8) & 0xffffefff;
      *(uint *)(this + 0xa8) = *(uint *)(this + 0xa8) | 0x2000;
    }
  }
  
  // Replace link1 head pointer at offset +0x118
  oldNodePtr = (int *)(this + 0x118);
  if (oldNodePtr != link1Node) {
    newNodeData = *link1Node;
    if (*oldNodePtr != newNodeData) {
      if (*oldNodePtr != 0) {
        // Release old node (function at 0x004daf90)
        FUN_004daf90(oldNodePtr);
      }
      *oldNodePtr = newNodeData;
      if (newNodeData != 0) {
        // Save the previous back-link of the new node, then set its back-link to &this->link1Head
        *(undefined4 *)(this + 0x11c) = *(undefined4 *)(newNodeData + 4);
        *(int **)(newNodeData + 4) = oldNodePtr;
      }
    }
  }
  *(int *)(this + 0x120) = link1Node[2];  // Store extra data from link1 node
  
  // Replace link2 head pointer at offset +0x124
  oldNodePtr = (int *)(this + 0x124);
  if (oldNodePtr != link2Node) {
    newNodeData = *link2Node;
    if (*oldNodePtr == newNodeData) {
      *(int *)(this + 300) = link2Node[2];  // +0x12C
      return;
    }
    if (*oldNodePtr != 0) {
      FUN_004daf90(oldNodePtr);
    }
    *oldNodePtr = newNodeData;
    if (newNodeData == 0) {
      *(int *)(this + 300) = link2Node[2];
      return;
    }
    *(undefined4 *)(this + 0x128) = *(undefined4 *)(newNodeData + 4);
    *(int **)(newNodeData + 4) = oldNodePtr;
  }
  *(int *)(this + 300) = link2Node[2];  // +0x12C
  return;
}