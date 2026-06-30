// FUNC_NAME: BehaviorTree::propagateState
void __thiscall BehaviorTree::propagateState(BehaviorTree *this, Node *node, Node *parentNode, char param4, bool param5, uint depth)
{
  byte childCount;
  byte childFlags;
  bool bRecurse;
  int childIndex;
  uint childNodeIndex;
  Node *childNode;
  
  if (this->m_bActive != '\0') {
    // Track maximum depth
    if (DAT_0112a540 < depth) {
      DAT_0112a540 = depth;
    }
    // If node and parentNode are valid
    if ((node != (Node *)0x0) && (parentNode != (Node *)0x0)) {
      childCount = parentNode->m_numChildren; // +0x14
      childIndex = 0;
      if (childCount != 0) {
        do {
          // Compute the index into the global child array (at this+0x24)
          // Child entry is 0x10 bytes, and contains a ushort at offset +4 that is the target node index
          childNodeIndex = (uint)(ushort)*(ushort *)((uint)(ushort)(parentNode->m_childBaseIndex + (short)childIndex) * 0x10 + 4 + this->m_pChildArray);
          // Get child node (array of 0x24-byte nodes at this+0x20)
          childNode = (Node *)(this->m_pNodeArray + childNodeIndex * 0x24);
          childFlags = childNode->m_flags; // +0x21
          // Check if child is eligible for propagation
          bRecurse = true;
          // If flag(0x01) set and flag(0x04) not set, or param4 non-zero and flag(0x08) set, then no recursion
          if ((((childFlags & 1) != 0) && ((childFlags & 4) == 0)) ||
             ((param4 != '\0' && ((childFlags & 8) != 0)))) {
            bRecurse = false;
          }
          // Check if bit2 (0x02) should be set or cleared based on param5
          if ((~(uint)(childFlags >> 1) & 1) == (param5 & 0xff)) {
            if (param5 == '\0') {
              // Clear bit2
              childNode->m_flags = childFlags & 0xfd;
            }
            else {
              // Set bit2; also if parent doesn't have flag(0x10), generate an ID and set it
              if ((parentNode->m_flags & 0x10) == 0) {
                undefined generatedId = FUN_006a8020(); // Generate unique ID (likely random)
                parentNode->m_flags |= 0x10;
                parentNode->m_id = generatedId; // +0x20, stores the generated ID
              }
              childNode->m_flags |= 2;
            }
            if (bRecurse) {
              // Recursively propagate to children of this child node
              propagateState(this, childNode, parentNode, param4, param5, depth + 1);
            }
          }
          childIndex++;
        } while (childIndex < childCount);
      }
    }
  }
}