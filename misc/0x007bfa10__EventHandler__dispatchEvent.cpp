// FUNC_NAME: EventHandler::dispatchEvent
void __thiscall EventHandler::dispatchEvent(uint this, int *eventData)
{
    char cVar1;
    int *piVar2;
    int iVar3;
    int iVar4;
    int eventType;
    float10 distance;
    undefined4 local_c;
    undefined4 local_8;
    uint local_4;

    piVar2 = eventData;
    validateEvent(eventData); // FUN_0046c6a0
    eventType = *piVar2;
    if (eventType == DAT_0120e93c) {
        releaseGlobal(&DAT_0120e93c); // FUN_004086d0
        if ((*(int *)(this + 0x4c) == 0) && (*(int *)(this + 0x50) == 0) &&
            (*(int *)(this + 0x54) == 0 && (*(int *)(this + 0x58) == 0))) {
LAB_007bfc57:
            destroyObject(-(uint)(this != 0x3c) & this); // FUN_004088c0
            return;
        }
        piVar2 = (int *)getChildObject(this + 0x4c, 0); // FUN_00446100
        if (piVar2 != (int *)0x0) {
            eventData = (int *)0x0;
            cVar1 = (**(code **)(*piVar2 + 0x10))(0x369ac561, &eventData); // virtual call
            scheduleCallback(-(uint)(cVar1 != '\0') & local_4); // FUN_0044b210
            return;
        }
    }
    else if (eventType == *(int *)(this + 0x30)) {
        addRef(this + 0x14); // FUN_00408680
        addRef(this + 0x1c); // FUN_00408680
        int *globalPtr = *(int **)(DAT_012233a0 + 4);
        if ((globalPtr != 0) && (globalPtr != (int *)0x1f30)) {
            int currentObj = 0;
            if (*(int *)(globalPtr + -0x2b8) == 0) {
                currentObj = 0;
            }
            else {
                currentObj = *(int *)(globalPtr + -0x2b8) + -0x48;
            }
            int thisObj = 0;
            if (*(int *)(this + 0x44) == 0) {
                thisObj = 0;
            }
            else {
                thisObj = *(int *)(this + 0x44) + -0x48;
            }
            if (((currentObj == thisObj) && (*(int *)(this + 0x44) != 0)) &&
                (*(int *)(this + 0x44) != 0x48)) {
                resetTimer(this + 0x5c, 0); // FUN_00402050
                if (*(int *)(this + 0x44) != 0) {
                    releaseObject(*(int *)(this + 0x44) + -0x48); // FUN_006d6930
                    return;
                }
                releaseObject(0); // FUN_006d6930
                return;
            }
        }
        local_c = *(undefined4 *)(this + 100);
        local_8 = 0;
        local_4 = local_4 & 0xffffff00;
        someLocalInit(&local_c, 0); // FUN_00408a00
        if (*(int *)(this + 0x28) != 0) {
            deleteChildObject((undefined4 *)(this + 0x28)); // FUN_004daf90
            *(undefined4 *)(this + 0x28) = 0;
            return;
        }
    }
    else {
        if (eventType == *(int *)(this + 0x38)) {
            releaseObject(this + 0x14); // FUN_004086d0
            releaseObject(this + 0x1c); // FUN_004086d0
            return;
        }
        if (eventType == *(int *)(this + 0x14)) {
            int *dataPtr = (int *)(piVar2[1] + 4);
            if ((dataPtr != 0) && (dataPtr = dataPtr + -0x48, dataPtr != 0)) {
                int foundObj = findObjectByHash(dataPtr, 0x383225a1); // FUN_006c9470
                if (foundObj != 0) {
                    if ((*(int *)(this + 0x44) != 0) && (*(int *)(this + 0x44) != 0x48)) {
                        int currentTarget = getCurrentTarget(); // FUN_00716c30
                        if (currentTarget != 0) {
                            int thisObj2 = 0;
                            if (*(int *)(this + 0x44) == 0) {
                                thisObj2 = 0;
                            }
                            else {
                                thisObj2 = *(int *)(this + 0x44) + -0x48;
                            }
                            if (currentTarget == thisObj2) {
                                int posA = getPosition(); // FUN_00471610
                                int posB = getPosition(); // FUN_00471610
                                distance = (float10)computeDistance(posA + 0x30, posB + 0x30); // FUN_0045c470
                                if (distance <= (float10)*(float *)(this + 0x40)) {
                                    resetTimer(this + 0x5c, 0); // FUN_00402050
                                }
                            }
                        }
                        releaseObject(currentTarget); // FUN_006d6930
                        return;
                    }
                    goto LAB_007bfc57;
                }
            }
        }
        else if (eventType == *(int *)(this + 0x1c)) {
            int *childPtr = (int *)(this + 0x28);
            int childObj = 0;
            if (*(int *)(this + 0x28) == 0) {
                childObj = 0;
            }
            else {
                childObj = *(int *)(this + 0x28) + -0x48;
            }
            int thisObj3 = 0;
            if (*(int *)(this + 0x44) == 0) {
                thisObj3 = 0;
            }
            else {
                thisObj3 = *(int *)(this + 0x44) + -0x48;
            }
            if (childObj == thisObj3) {
                resetTimer(this + 100, 0); // FUN_00402050 at offset 0x64
            }
            if (*childPtr != 0) {
                deleteChildObject(childPtr); // FUN_004daf90
                *childPtr = 0;
            }
        }
    }
    return;
}