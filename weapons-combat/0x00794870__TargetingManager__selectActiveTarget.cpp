// FUNC_NAME: TargetingManager::selectActiveTarget
// Function at 0x00794870: Decides which of two interactable objects (global current and candidate) to activate based on distance to player.
// param_1: this (TargetingManager*)
// param_2: candidate interactable object (some handle/pointer)
void __thiscall TargetingManager::selectActiveTarget(TargetingManager* thisPtr, int candidateObject)
{
    int currentObject;
    float rangeSq;
    int playerEntity1;
    int playerEntity2;
    float dx, dy, dz;
    float distSq;

    // Get the currently active interactable object from a global manager (likely via a singleton)
    currentObject = (**(code**)(*(int*)(*(int*)(DAT_012233a0 + 4) + 0xc)))();

    // If there is a current object and it's different from the candidate
    if ((currentObject != 0) && (candidateObject != currentObject)) {
        // Compute squared interaction range from this manager's field (+0x334) multiplied by a global factor
        rangeSq = *(float*)(thisPtr + 0x334) * DAT_00d5eee4;
        rangeSq = rangeSq * rangeSq; // square the range

        // Get player entity (or current camera entity) twice? Possibly two different entities?
        // FUN_00471610 likely returns a pointer to an entity with position at offsets +0x30, +0x34, +0x38
        playerEntity1 = FUN_00471610();
        playerEntity2 = FUN_00471610();

        // Compute squared distance between the two entities' positions
        dx = *(float*)(playerEntity2 + 0x30) - *(float*)(playerEntity1 + 0x30);
        dy = *(float*)(playerEntity2 + 0x34) - *(float*)(playerEntity1 + 0x34);
        dz = *(float*)(playerEntity2 + 0x38) - *(float*)(playerEntity1 + 0x38);
        distSq = dx*dx + dy*dy + dz*dz;

        // If the distance is within range, activate the current object and return
        if (distSq < rangeSq) {
            FUN_00793a00(currentObject); // activate/set active
            return;
        }
    }

    // Otherwise activate the candidate object
    FUN_00793a00(candidateObject);
}