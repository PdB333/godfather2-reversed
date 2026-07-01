// FUNC_NAME: Entity::copyWorldMatrixWithCulling

void __thiscall Entity::copyWorldMatrixWithCulling(Entity* this, float* outMatrix, Vector3* viewerPosition, float* inMatrix)
{
    // Offset +0x3D4: cullingEnabled flag (bool)
    if (*(int*)((char*)this + 0x3D4) == 0)
    {
        // Culling disabled: just copy the matrix
        for (int i = 0; i < 16; i++)
        {
            outMatrix[i] = inMatrix[i];
        }
        return;
    }

    // Extract source position from inMatrix (translation column)
    float srcPosX = inMatrix[12];
    float srcPosY = inMatrix[13];
    float srcPosZ = inMatrix[14];

    // Viewer position assumed to be at offset +0x30 from viewerPosition struct
    float viewerX = *(float*)((char*)viewerPosition + 0x30);
    float viewerY = *(float*)((char*)viewerPosition + 0x34);
    float viewerZ = *(float*)((char*)viewerPosition + 0x38);

    float dx = viewerX - srcPosX;
    float dy = viewerY - srcPosY;
    float dz = viewerZ - srcPosZ;
    float distSq = dx*dx + dy*dy + dz*dz;

    // Global culling distance squared (DAT_00d71c4c)
    if (distSq < g_sqrMaxCullDistance)
    {
        int occlusionResult = 0;
        // Check line of sight between viewer and source position
        bool visible = checkLineOfSight(&viewerX, &srcPosX, 0, 0, &occlusionResult);
        if (visible)
        {
            // Visible: copy matrix immediately
            for (int i = 0; i < 16; i++)
            {
                outMatrix[i] = inMatrix[i];
            }
            return;
        }
    }

    // Default copy (when culling enabled but object not within distance or not visible)
    for (int i = 0; i < 16; i++)
    {
        outMatrix[i] = inMatrix[i];
    }
}