//FUNC_NAME: Camera::computeAimOffsets
void __thiscall Camera::computeAimOffsets(void* this, int unused, float* outCameraPos, float* outLookAtPos)
{
    float fScale1;
    int pOwner;
    float* pOwnerFloats;
    float offset[3]; // from computeCameraOffset
    float vec1[3];   // from owner transform (first call)
    float vec2[3];   // from owner transform (second call)

    // Get owner object (likely player or vehicle)
    pOwner = getOwnerTransform(); // FUN_00471610
    // Compute vector from owner's target position (offset 0x20,0x24,0x28) to some reference
    vec2[0] = g_fSomeConstant - *(float*)(pOwner + 0x20);
    vec2[1] = g_fSomeConstant - *(float*)(pOwner + 0x24);
    vec2[2] = g_fSomeConstant - *(float*)(pOwner + 0x28);

    // Get owner transform again (same pointer)
    pOwnerFloats = (float*)getOwnerTransform(); // FUN_00471610
    // Compute vector from owner's position (offset 0,4,8) to reference
    vec1[0] = g_fSomeConstant - *pOwnerFloats;
    vec1[1] = g_fSomeConstant - pOwnerFloats[1];
    vec1[2] = g_fSomeConstant - pOwnerFloats[2];

    // Compute camera offset (likely based on FOV or distance)
    computeCameraOffset(&offset); // FUN_008970a0

    // Apply additive offset to Y component
    offset[1] = offset[1] + g_fAdditiveOffset;

    // Determine camera mode from member at +0x118
    int cameraMode = *(int*)((char*)this + 0x118);
    if (cameraMode == 1) {
        // First-person or shoulder camera
        outCameraPos[0] = vec1[0] * g_fScaleFactor1 + offset[0];
        outCameraPos[1] = vec1[1] * g_fScaleFactor1 + offset[1];
    } else if (cameraMode == 2) {
        // Third-person or chase camera
        outCameraPos[0] = *pOwnerFloats * g_fScaleFactor1 + offset[0];
        outCameraPos[1] = pOwnerFloats[1] * g_fScaleFactor1 + offset[1];
        vec1[2] = pOwnerFloats[2]; // override Z component
    } else {
        // Unknown mode, skip output
        goto LAB_007c6629;
    }
    outCameraPos[2] = vec1[2] * g_fScaleFactor1 + offset[2];

LAB_007c6629:
    // Compute look-at point as camera position plus scaled vector from owner target
    fScale1 = g_fScaleFactor2;
    outLookAtPos[0] = vec2[0] * fScale1 + outCameraPos[0];
    outLookAtPos[1] = vec2[1] * fScale1 + outCameraPos[1];
    outLookAtPos[2] = vec2[2] * fScale1 + outCameraPos[2];
    return;
}