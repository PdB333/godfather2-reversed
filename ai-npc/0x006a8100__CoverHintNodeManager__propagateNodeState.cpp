// FUNC_NAME: CoverHintNodeManager::propagateNodeState
void __thiscall CoverHintNodeManager::propagateNodeState(void* thisNode, CoverHintNode* currentNode, ChildDescriptor* childDesc, bool force, bool newState, int depth) {
    int loopIdx;
    byte childByte;
    byte nodeFlagByte;
    bool recurse;
    int childNodePtr;
    char tempByte;
    uint childIndex;
    int baseNodeArray;
    int childOffsetBase;

    // +0x10: enable flag for this manager instance
    if (*(char*)((int)thisNode + 0x10) != '\0') {
        // Track maximum recursion depth globally
        if (DAT_0112a540 < depth) {
            DAT_0112a540 = depth;
        }
        if (currentNode != nullptr && childDesc != nullptr) {
            byte childCount = *(byte*)((int)childDesc + 0x14); // +0x14: number of children
            loopIdx = 0;
            if (childCount != 0) {
                do {
                    // childOffsetBase from node array base (thisNode+0x24)
                    childOffsetBase = *(int*)((int)currentNode + 0x24); // +0x24: offset base for child indices
                    // Compute child index: (base_short + loopIdx) * 16 + 4 + childOffsetBase, read a ushort index
                    childIndex = (uint)*(ushort*)(((uint)(ushort)(*(short*)((int)childDesc + 0x10) + (short)loopIdx) * 0x10) + 4 + childOffsetBase);
                    // Base pointer to node array (thisNode+0x20)
                    baseNodeArray = *(int*)((int)currentNode + 0x20); // +0x20: base pointer to node array (0x24 bytes per node)
                    nodeFlagByte = *(byte*)(baseNodeArray + 0x21 + childIndex * 0x24); // +0x21: flags byte per node
                    childNodePtr = baseNodeArray + childIndex * 0x24;

                    recurse = true;
                    // Condition: if (bit0 set and bit2 clear) OR (force and bit3 set) -> don't recurse into this child
                    if (((nodeFlagByte & 1) != 0 && (nodeFlagByte & 4) == 0) || (force && (nodeFlagByte & 8) != 0)) {
                        recurse = false;
                    }
                    // Check if the child should be modified: bit1 state matches newState?
                    if ((~((uint)(nodeFlagByte >> 1)) & 1) == (newState & 0xff)) {
                        if (newState == 0) {
                            // Clear bit1 (set to 0)
                            *(byte*)(childNodePtr + 0x21) = nodeFlagByte & 0xfd;
                        } else {
                            // Set bit1 (set to 1)
                            if ((*(byte*)((int)childDesc + 0x21) & 0x10) == 0) {
                                // First time activation: call helper to get some value, set bit4
                                tempByte = FUN_006a8020();
                                *(byte*)((int)childDesc + 0x21) |= 0x10;
                                *(char*)((int)childDesc + 0x20) = tempByte;
                            }
                            *(byte*)(childNodePtr + 0x21) |= 2;
                        }
                        if (recurse) {
                            // Recursively process child's children with increased depth
                            propagateNodeState(thisNode, childNodePtr, childDesc, force, newState, depth + 1);
                        }
                    }
                    loopIdx++;
                } while (loopIdx < childCount);
            }
        }
    }
    return;
}