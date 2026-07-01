// FUNC_NAME: ObjectiveManager::removeObjective
void __thiscall ObjectiveManager::removeObjective(int objectiveID)
{
    uint index;
    int missionIndex;
    int* objectivePtr;

    // Search for the objective ID in the objectives array (at +0x1A4, count at +0x1A8)
    index = 0;
    if (this->objectiveCount != 0) {
        objectivePtr = this->objectiveArray;
        do {
            if (objectivePtr->id == objectiveID) goto LAB_008c11c3;
            index = index + 1;
            objectivePtr = objectivePtr + 1;
        } while (index < this->objectiveCount);
    }
    index = 0xFFFFFFFF; // Not found

LAB_008c11c3:
    // If this manager is type 0x637b907 (e.g., HitMission), we need to clear the associated mission objective
    if (this->managerType == 0x637b907) {
        missionIndex = findMissionByObjective(objectiveID); // FUN_0090b0a0
        if (missionIndex != -1) {
            clearMissionObjective(missionIndex, 0); // FUN_0090b5d0
        }
    }

    // If the objective was found in the array, remove it
    if ((int)index >= 0) {
        int* objEntry = this->objectiveArray[index]; // Pointer to objective entry
        pauseObjectiveUpdates(0); // FUN_008c8a80
        stopTrackedObjective(objectiveID); // FUN_008beec0
        unlockUIState(0); // FUN_00790110
        removeObjectiveAtIndex(index); // FUN_008bdeb0

        // If the entry still exists (should be null after removal, but check)
        if (objEntry != 0) {
            recalcObjectiveList(); // FUN_008c80c0
            destroyObjective(objEntry); // FUN_009c8eb0
        }
    }
    return;
}