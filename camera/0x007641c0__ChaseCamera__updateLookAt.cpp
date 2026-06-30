// FUNC_NAME: ChaseCamera::updateLookAt
// Function address: 0x007641c0
// Role: Computes the direction from the camera to its target and sets the camera's orientation.
// Uses a target component (offset +0x78) and a global entity position function.

void __thiscall ChaseCamera::updateLookAt(void* this, void* pUpdateData)
{
    // +0x58 : active flag (e.g., bTargetingActive)
    if (*(int*)((uintptr_t)this + 0x58) == 0)
        return;

    // +0x78 : pointer to target object (e.g., mpTargetEntity)
    void* pTarget = *(void**)((uintptr_t)this + 0x78);
    if (pTarget == nullptr)
        return;

    // +0x88 : target's position validity flag (bPosValid)
    if (*(int*)((uintptr_t)pTarget + 0x88) == 0)
        return;

    // +0x90 : pointer to target's position vector (float[3]) (mpPos)
    float* pTargetPos = *(float**)((uintptr_t)pTarget + 0x90);
    if (pTargetPos == nullptr)
        return;

    // Get own position structure from global function (returns pointer to a struct)
    void* pPosData = (void*)FUN_00471610();
    if (pPosData == nullptr)
        return;

    // Read own position: two floats at offset 0x30 (packed as a double for x and y), then z at 0x38
    float ownX = *(float*)((uintptr_t)pPosData + 0x30);
    float ownY = *(float*)((uintptr_t)pPosData + 0x34); // second float from the packed pair
    float ownZ = *(float*)((uintptr_t)pPosData + 0x38);

    // Target position (x,y,z as three floats)
    float targetX = pTargetPos[0];
    float targetY = pTargetPos[1];
    float targetZ = pTargetPos[2];

    // Compute direction vector from own position to target
    float deltaX = targetX - ownX;
    float deltaY = targetY - ownY;
    float deltaZ = targetZ - ownZ;

    // Store target position (x,y as packed double? or two floats) and delta in preparation for orientation update
    // The first argument (0) is a flag, second is &targetX (treated as two floats), third is &deltaX (start of 3-float vector), fourth is count (1)
    FUN_00601760(0, &targetX, &deltaX, 1);

    // Normalize the direction vector (deltaX, deltaY, deltaZ)
    FUN_0043a210(&deltaX, &deltaX);

    // Set orientation of the camera (or entity) based on the normalized direction
    // pUpdateData likely contains additional parameters; zeros are flags (e.g., rotation axes)
    FUN_00600210(pUpdateData, 0, 0, 0);

    // Final update call (e.g., apply rotation to camera matrix)
    FUN_00763ff0();
}