// FUNC_NAME: MissionObjective::processObjective
bool MissionObjective::processObjective(int excludeId)
{
    int *linkPtr;
    int *endPtr;
    bool found;
    int *current;
    int index;
    float delay;
    int mode;
    int *gMgr = *(int **)(DAT_01223428 + 0x24); // g_ObjectiveManager->arrayBase

    linkPtr = (int *)(this + 0x1c);  // +0x1c: start of ObjectiveLink array
    endPtr  = (int *)(this + 0x5c);  // +0x5c: end pointer (exclusive)
    mode = *(int *)(this + 0x18);    // +0x18: mode (0 = wait for all complete, 1 = wait for any complete)

    // Mode 0: check if any incomplete objective exists
    if (mode == 0) {
        for (; linkPtr != endPtr; linkPtr += 2) {
            if (*linkPtr != 0) {
                // Check if objective at index linkPtr[1] is still active (global flag == 0)
                int *objArray = gMgr;
                int objState = *(int *)(objArray + 8 + linkPtr[1] * 0x14); // offset +8 in each 0x14-byte entry
                if (objState == 0) {
                    return false;
                }
            }
        }
    }
    // Mode 1: find first objective that is active (non-zero pointer AND global flag non-zero)
    else if (mode == 1) {
        if (linkPtr == endPtr) {
            return false;
        }
        while (true) {
            if (*linkPtr != 0) {
                int *objArray = gMgr;
                int objState = *(int *)(objArray + 8 + linkPtr[1] * 0x14);
                if (objState != 0) {
                    break; // active objective found
                }
            }
            linkPtr += 2;
            if (linkPtr == endPtr) {
                return false;
            }
        }
    }
    // Unknown mode → fail
    else {
        return false;
    }

    // If excludeId is not -1, deactivate all other objectives except the one identified
    if (excludeId != -1) {
        for (current = (int *)(this + 0x1c); current != endPtr; current += 2) {
            if (*current != 0 && current[1] != excludeId) {
                FUN_00441e00(); // notifyOtherObjectiveDeactivated()
            }
        }
    }

    delay = *(float *)(this + 0x14); // +0x14: delay before effect
    if (delay > 0.0f) {
        // Allocate a temporary (size 0xC) and call constructor on base object (this - 0x50)
        int *temp = (int *)FUN_009c8e50(0xC); // operator new(0xC)
        if (temp == 0) {
            return false;
        }
        int param = FUN_0045ca00(this - 0x50); // baseObject->someInit()
        // Schedule a delayed event (target: this+0xC, event type 0, with delay, param, and extra 0)
        FUN_00440590(this + 0xC, 0, delay, param, 0);
        return true;
    }

    // No delay: immediate completion path
    // Setup a virtual call by preparing a temporary object on stack
    void **vtablePtr = &PTR_FUN_00e31e2c; // global vtable
    int localVar2 = 0;
    int localVar1 = this + 0xC; // some context
    // Inline vtable/member initialisation
    int *pLocalVar = &localVar1;
    // ...
    FUN_00408a00(&localVar1, 0); // function that uses the stack variables
    FUN_0045cac0();              // cleanup
    return true;
}