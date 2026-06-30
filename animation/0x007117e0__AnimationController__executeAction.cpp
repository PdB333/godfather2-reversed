// FUNC_NAME: AnimationController::executeAction
void __thiscall AnimationController::executeAction(void *context, ActionData *actionData)
{
    char isValidAction;
    char isActionActive;
    int actionResult;
    int *resourcePtr;
    int *mainResourcePtr;
    int resourceIndex;
    float actionSpeed;
    undefined8 spawnedObject;
    undefined4 retAddr;
    bool actionOk;
    bool isResourceActive;
    int resourceIds[4];

    // Check if action data has a secondary resource pointer
    if (actionData->secondaryResourcePtr == 0) {
        mainResourcePtr = nullptr;
    } else {
        mainResourcePtr = (int *)(actionData->secondaryResourcePtr - 0x48);
    }

    // Validate action data: must have a primary resource and size must be 0x48
    if ((actionData->primaryResourcePtr != 0) && (actionData->size != 0x48)) {
        actionOk = false;
        // If action type is "command" (3)
        if (actionData->actionType == 3) {
            if (actionData->primaryResourcePtr == 0) {
                resourcePtr = nullptr;
            } else {
                resourcePtr = (int *)(actionData->primaryResourcePtr - 0x48);
            }
            isResourceActive = 0;
            // Query if this resource has the specified action hash
            isValidAction = ((int (*)(int, int*))resourcePtr->vtable->method0x10)(0xa5975eb2, &isResourceActive);
            if ((isValidAction != 0) && (isResourceActive != 0) &&
                (isValidAction = FUN_00543390(resourceIds, 4), isValidAction != 0)) {
                resourceIndex = 0;
                int count = FUN_00543370();
                if (0 < count) {
                    do {
                        if (3 < resourceIndex) break;
                        if (resourceIds[resourceIndex] != 0) {
                            mainResourcePtr = (int *)resourceIds[resourceIndex];
                            break;
                        }
                        resourceIndex = resourceIndex + 1;
                        count = FUN_00543370();
                    } while (resourceIndex < count);
                }
            }
        }

        // Get action speed from the animation object of this controller
        actionSpeed = ((float (*)(int*))this->animationObj->vtable->method0xBC)(mainResourcePtr);
        if (actionSpeed != 0.0f) {
            actionResult = FUN_0071ce70(mainResourcePtr);
            isValidAction = '\0';
            if (actionResult == 0) {
                // No previous action running - start new
                actionOk = false;
                isActionActive = ((int (*)(int, bool*))mainResourcePtr->vtable->method0x10)(0x55859efa, &actionOk);
                if ((isActionActive == 0) || (actionOk == false)) {
                    return;
                }
                actionResult = FUN_007112c0(mainResourcePtr, retAddr);
                if (actionResult == 0) {
                    return;
                }
                FUN_0071bf70(*(int *)(context + 0x2c), retAddr);
            } else {
                // Interrupt current action
                FUN_0071bfa0(*(int *)(context + 0x2c), retAddr);
                isValidAction = FUN_0071c320(retAddr);
            }
            // Finalize action
            FUN_0071bfd0(retAddr);
            // Set flag at offset 0x3c in the action result object
            *(ushort *)(actionResult + 0x3c) |= 2;

            // Check if we need to spawn a visual effect or something
            isActionActive = FUN_0072f180(mainResourcePtr);
            if (isActionActive == 0) {
                spawnedObject = FUN_00711380(*(int *)(context + 0x30));
                FUN_00714db0((int)((ulonglong)spawnedObject >> 0x20), *(int *)(this->animationObj), (int)spawnedObject);
            }

            // Post-action cleanup
            if (isValidAction == 0) {
                if ((*(uint *)(context + 0x30) & 0x80000c) != 0) {
                    FUN_0071c720(*(int *)(this->animationObj), mainResourcePtr, DAT_01205228);
                    return;
                }
                FUN_0071c770(*(int *)(this->animationObj), mainResourcePtr);
            }
        }
    }
}