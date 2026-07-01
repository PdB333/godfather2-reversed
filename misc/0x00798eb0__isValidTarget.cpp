// FUNC_NAME: isValidTarget
bool isValidTarget(int targetEntity) {
    int bGlobalActive = checkGlobalCondition(0xc4bc3ce7, 0);
    int currentEntity = 0;
    if (bGlobalActive != 0) {
        currentEntity = getCurrentEntity();
        if (currentEntity != 0) {
            int sourcePos = getActivePosition();  // first call – source entity position
            int targetPos = getActivePosition();  // second call – target entity position
            float dx = *(float*)(targetPos + 0x30) - *(float*)(sourcePos + 0x30);
            float dy = *(float*)(targetPos + 0x34) - *(float*)(sourcePos + 0x34);
            float dz = *(float*)(targetPos + 0x38) - *(float*)(sourcePos + 0x38);
            float distSq = dx*dx + dy*dy + dz*dz;
            if (gSquaredDistanceThreshold < distSq) {
                currentEntity = 0;
            }
        }
    }
    bool result = true;
    if ((targetEntity == 0) || (currentEntity == 0) || (targetEntity == currentEntity)) {
        result = false;
    }
    return result;
}