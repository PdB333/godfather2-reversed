// FUNC_NAME: CoverHintNodeManager::isNodeWithinRange
bool __thiscall CoverHintNodeManager::isNodeWithinRange(float* currentDistance, int nodeIndex) {
    int initStatus = FUN_005dc670(this);
    float nodeDistance;
    if (initStatus != 0) {
        FUN_005dd8a0(nodeIndex, &nodeDistance);
        if ((nodeDistance >= 0.0f) && (nodeDistance <= g_maxCoverDistance) && (*currentDistance >= 0.0f)) {
            return true;
        }
    }
    return false;
}