// FUNC_NAME: CoverHintNodeManager::addCoverNode
bool __thiscall CoverHintNodeManager::addCoverNode(void* thisPtr, CoverNode* nodeList, float* nodePos, float* targetPos)
{
    // +0x04: float maxDistance
    // +0x18c: int nodeCount (max 32)
    bool hasRoom = *(int*)((char*)thisPtr + 0x18c) < 32;
    if (hasRoom) {
        // Check node validity: flag at +0x21 bit 0 must be clear, and flags at +0x18 bits 14-15 must be 0
        if (((*(unsigned char*)((char*)nodePos + 0x21) & 1) == 0) &&
            ((*(unsigned int*)((char*)nodePos + 0x18) & 0xC000) == 0) &&
            // Distance squared between node and target must be less than maxDistance
            ((nodePos[2] - targetPos[2]) * (nodePos[2] - targetPos[2]) +
             (nodePos[1] - targetPos[1]) * (nodePos[1] - targetPos[1]) +
             (nodePos[0] - targetPos[0]) * (nodePos[0] - targetPos[0]) < *(float*)((char*)thisPtr + 4))) {
            // Check if node is already in list or blocked (returns non-zero if so)
            if (isNodeValidForAddition(nodePos, targetPos) == 0) {
                addNodeToList(nodeList, nodePos);
                *(int*)((char*)thisPtr + 0x18c) += 1;
                return true;
            }
        }
        hasRoom = *(int*)((char*)thisPtr + 0x18c) < 32;
    }
    return !hasRoom;
}