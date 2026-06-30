// FUNC_NAME: ConditionEvaluator::evaluateCondition
bool __thiscall ConditionEvaluator::evaluateCondition(int this, int param2, int param3, int conditionId, int extraData)
{
    float distance;
    bool boolResult;
    bool flagCheck;
    char charResult;
    char unknown;
    int* componentPtr;
    int playerPtr;
    int entityPtr;
    int localPtr;
    
    entityPtr = *(int*)(this + 0x5c);  // +0x5c: entity component pointer
    unknown = 0;
    switch(conditionId - 0x12) {
    case 0:
        componentPtr = (int*)getActionState(entityPtr);
        if (componentPtr == (int*)0x0) {
            return false;
        }
        charResult = isAlive();
        if (charResult == '\0') {
            return false;
        }
        // Check if state flag 0x20 is set
        flagCheck = (**(code **)(*componentPtr + 0x1c))(0x20);
        goto LAB_CheckReturn;
    case 1:
        componentPtr = (int*)getActionState(entityPtr);
        if (componentPtr == (int*)0x0) {
            return false;
        }
        charResult = isAlive();
        if (charResult == '\0') {
            return false;
        }
        flagCheck = (**(code **)(*componentPtr + 0x1c))(0x10);
        goto LAB_CheckReturn;
    case 2:
        componentPtr = (int*)getActionState(entityPtr);
        if (componentPtr == (int*)0x0) {
            return false;
        }
        charResult = isAlive();
        if (charResult == '\0') {
            return false;
        }
        flagCheck = (**(code **)(*componentPtr + 0x1c))(0x80);
        goto LAB_CheckReturn;
    case 3:
        componentPtr = (int*)getActionState(entityPtr);
        if (componentPtr == (int*)0x0) {
            return false;
        }
        charResult = isAlive();
        if (charResult == '\0') {
            return false;
        }
        flagCheck = (**(code **)(*componentPtr + 0x1c))(0x40);
LAB_CheckReturn:
        if (flagCheck) {
            return true;
        }
        break;
    case 4:
        if (entityPtr == 0) {
            return false;
        }
        charResult = isPlayerControlled();
        if (charResult != '\0') {
            return false;
        }
        playerPtr = getPlayer();
        if (playerPtr == 0) {
            return false;
        }
        // Check bit 13 at offset +0x1f58
        flagCheck = (*(uint*)(entityPtr + 0x1f58) >> 0xd) & 1;
        goto LAB_CheckReturn;
    case 5:
        localPtr = getActionState(entityPtr);
        if (localPtr != 0) {
            if (*(int**)(localPtr + 0x1c) == (int*)0x0) {
                return false;
            }
            if (*(int**)(localPtr + 0x1c) == (int*)0x48) {
                return false;
            }
            playerPtr = getPlayer();
            if (playerPtr == 0) {
                return false;
            }
            charResult = isInCombat();
            if (charResult == '\0') {
                charResult = checkGameStateFlag(0x4f);
                if (charResult == '\0') {
                    return false;
                }
                return true;
            }
            return true;
        }
        break;
    case 6:
        localPtr = getActionState(entityPtr);
        if ((((localPtr != 0) &&
              (*(int**)(localPtr + 0x1c) != (int*)0x0)) &&
             ((*(int**)(localPtr + 0x1c) != (int*)0x48 &&
               (charResult = isPlayerControlled(), charResult == '\0')))) &&
            ((localPtr = getPlayer(),
              localPtr == 0 || (charResult = checkGameStateFlag(0x50), charResult != '\0')))) {
            playerPtr = getPlayer();
            if (playerPtr == 0) {
                return false;
            }
            charResult = checkGameStateFlag(0x5a);
            if (charResult != '\0') {
                return false;
            }
            // Note: caller reuses playerPtr from getPlayer() but in code it's second call
            localPtr = getPlayer();
            charResult = hasLineOfSight(entityPtr, localPtr);
            if (charResult != '\0') {
                return false;
            }
            return true;
        }
        break;
    case 7:
        localPtr = getActionState(entityPtr);
        if (localPtr != 0) {
            if (((*(int*)(localPtr + 0x1c) != 0) && (*(int*)(localPtr + 0x1c) != 0x48)) &&
                (localPtr = getPlayer(), localPtr != 0)) {
                return false;
            }
            playerPtr = getPlayer();
            if (playerPtr != 0) {
                return false;
            }
            charResult = checkGameStateFlag(0x4f);
            if (charResult != '\0') {
                return false;
            }
            return true;
        }
        break;
    case 8:
        playerPtr = getPlayer();
        if (playerPtr == 0) {
            return false;
        }
        charResult = isInCombat();
        if (charResult == '\0') {
            return false;
        }
        return true;
    default:
        unknown = evaluateDefaultCondition(param2, param3, conditionId, extraData);
        break;
    case 10:
        charResult = checkSomeCondition(entityPtr, 1);
        return charResult == '\0';
    case 0xb:
        localPtr = getActionState(entityPtr);
        if ((localPtr == 0) || (charResult = isInVehicle(), charResult == '\0')) {
            boolResult = false;
        } else {
            boolResult = true;
        }
        charResult = isMoving(entityPtr);
        if (charResult == '\0') {
            return false;
        }
        if (boolResult) {
            return false;
        }
        return true;
    case 0xc:
        distance = *(float*)(extraData + 4);
        charResult = getDistanceToPlayer();
        if ((charResult != '\0') && (distance < *(float*)(this + 0x30))) {  // +0x30: distance threshold
            return true;
        }
        return false;
    case 0xd:
        if (*(int*)(this + 0x20) == 0) {  // +0x20: active/controlled flag
            return *(int*)(entityPtr + 0x24ec) != 0;  // +0x24ec: some state flag
        }
        break;
    case 0xe:
        if (*(int*)(this + 0x20) == 0) {
            return *(int*)(entityPtr + 0x24ec) == 0;
        }
        break;
    case 0xf:
        charResult = isPlayerControlled();
        if (charResult != '\0') {
            return true;
        }
        if ((*(byte*)(this + 0x3b) & 1) != 0) {  // +0x3b: bitfield
            return true;
        }
        return false;
    case 0x11:
        entityPtr = getActionState(entityPtr);
        if ((entityPtr != 0) && (charResult = isAlive(), charResult == '\0')) {
            return true;
        }
    }
    return unknown;
}