// FUNC_NAME: TargetingManager::findClosestTarget
// Address: 0x0097c890
// Role: Finds the nearest target from multiple object lists to a given position,
//       with priority for a specific target ID. Updates current target and notifies callbacks.

void __thiscall TargetingManager::findClosestTarget(float *targetPosition)
{
    int closestId = 0;
    int category = 0;
    float closestDistSq = DAT_00d5f6f0; // Large initial distance (likely FLT_MAX)
    bool foundPriority = false;

    // List 1: offset +0x10, count at +0x30
    if (*(int *)(this + 0x30) != 0) {
        int *listPtr = (int *)(this + 0x10);
        for (uint i = 0; i < *(uint *)(this + 0x30); i++) {
            float distSq = DAT_00d5f6f0;
            if (*listPtr == *(int *)(this + 0xa4)) { // Priority target ID
                closestId = *(int *)(this + 0x10 + i * 4);
                category = 1;
                foundPriority = true;
                break;
            }
            float *objPos = (float *)FUN_00950b20(); // Get object position
            if (objPos != nullptr) {
                float dx = *objPos - *targetPosition;
                float dz = objPos[2] - targetPosition[2];
                distSq = dx * dx + dz * dz;
            }
            if (distSq < closestDistSq) {
                closestId = *listPtr;
                category = 1;
                closestDistSq = distSq;
            }
            listPtr++;
        }
    }

    // List 2: offset +0x34, count at +0x54
    if (*(int *)(this + 0x54) != 0) {
        int *listPtr = (int *)(this + 0x34);
        for (uint i = 0; i < *(uint *)(this + 0x54); i++) {
            float distSq = DAT_00d5f6f0;
            if (foundPriority) break;
            if (*listPtr == *(int *)(this + 0xa4)) {
                closestId = *(int *)(this + 0x34 + i * 4);
                category = 2;
                foundPriority = true;
                break;
            }
            float *objPos = (float *)FUN_00950b20();
            if (objPos != nullptr) {
                float dx = *objPos - *targetPosition;
                float dz = objPos[2] - targetPosition[2];
                distSq = dx * dx + dz * dz;
            }
            if (distSq < closestDistSq) {
                closestId = *listPtr;
                category = 2;
                closestDistSq = distSq;
            }
            listPtr++;
        }
    }

    // List 3: offset +0x58, count at +0x78
    if (*(int *)(this + 0x78) != 0) {
        int *listPtr = (int *)(this + 0x58);
        for (uint i = 0; i < *(uint *)(this + 0x78); i++) {
            float distSq = DAT_00d5f6f0;
            if (foundPriority) break;
            if (*listPtr == *(int *)(this + 0xa4)) {
                closestId = *(int *)(this + 0x58 + i * 4);
                category = 3;
                foundPriority = true;
                break;
            }
            float *objPos = (float *)FUN_00950b20();
            if (objPos != nullptr) {
                float dx = *objPos - *targetPosition;
                float dz = objPos[2] - targetPosition[2];
                distSq = dx * dx + dz * dz;
            }
            if (distSq < closestDistSq) {
                closestId = *listPtr;
                category = 3;
                closestDistSq = distSq;
            }
            listPtr++;
        }
    }

    // List 4: offset +0x7c, count at +0x9c (objects have position at +0x10 and +0x18)
    if (*(int *)(this + 0x9c) != 0) {
        int *listPtr = (int *)(this + 0x7c);
        for (uint i = 0; i < *(uint *)(this + 0x9c); i++) {
            if (foundPriority) break;
            int objId = *listPtr;
            if (objId == *(int *)(this + 0xa4)) {
                closestId = *(int *)(this + 0x7c + i * 4);
                category = 4;
                break;
            }
            float dx = *(float *)(objId + 0x10) - *targetPosition;
            float dz = *(float *)(objId + 0x18) - targetPosition[2];
            float distSq = dx * dx + dz * dz;
            if (distSq < closestDistSq) {
                category = 4;
                closestId = objId;
                closestDistSq = distSq;
            }
            listPtr++;
        }
    }

    // Update current target if changed and valid
    if (*(int *)(this + 0xa0) != closestId && closestId != 0 && category != 0) {
        *(int *)(this + 0xa0) = closestId; // Update current target ID

        // Notify callbacks (array at +0xd8, count at +0xdc)
        int callbackCount = *(int *)(this + 0xdc);
        if (callbackCount != 0) {
            int *callbackArray = *(int **)(this + 0xd8);
            for (uint i = 0; i < callbackCount; i++) {
                int callbackObj = *(int *)(callbackArray + i);
                int vtable = **(int **)callbackObj;
                switch (category) {
                    case 1:
                        (*(void (__thiscall **)(int, int))(vtable + 8))(callbackObj, closestId);
                        break;
                    case 2:
                        (*(void (__thiscall **)(int, int))(vtable + 0xc))(callbackObj, closestId);
                        break;
                    case 3:
                        (*(void (__thiscall **)(int, int))(vtable + 0x10))(callbackObj, closestId);
                        break;
                    case 4:
                        (*(void (__thiscall **)(int, int))(vtable + 0x14))(callbackObj, closestId);
                        break;
                }
            }
        }
    }
}