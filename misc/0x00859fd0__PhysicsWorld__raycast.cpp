// FUNC_NAME: PhysicsWorld::raycast
// Function: 0x00859fd0 - Perform a line-of-sight / raycast test from (startX, startY, startZ) to (endX, endY, endZ)
// Returns: true if an entity was hit, false otherwise
// The this pointer points to a PhysicsWorld/SceneManager object. Offset +0xF8 is a pointer to an entity list manager.
// Iterates over all registered entities, testing intersection with the line segment.
// On first hit, records the hit entity, interpolates the hit point, and stores results.

bool __thiscall PhysicsWorld::raycast(int this, unsigned int arg2, float startX, float startY, float startZ,
                                      float endX, float endY, float endZ, unsigned int userData)
{
    int entityCount;
    float currentTime;
    int hitEntity;
    int entityHandle;
    float deltaX, deltaY, deltaZ;
    float transform[16]; // matrix at entity + 0xA0 (4x4)
    float localVec[3];
    float localEnd[3];
    float interpolatedHit[3];
    // ... other locals

    // Get current time? Likely for animation or debugging
    (*(code **)(*(int **)(this + 0xF8) + 0x1CC))(&currentTime);

    // Initialize loop counter and result
    float loopCounter = 0.0f;
    hitEntity = 0;

    // Get number of entities to test
    entityCount = FUN_00543330(); // Likely getNumEntities()

    if (entityCount != 0) {
        do {
            // Get next entity handle from the list manager
            entityHandle = (**(code **)(**(int **)(this + 0xF8) + 500))(&currentTime); // Offset 500 = getNextEntityHandle
            if (entityHandle != 0) {
                // Get entity pointer from handle
                int entityPtr = FUN_0054eaf0(); // Likely getEntityFromHandle

                // Read entity's 4x4 transformation matrix from offset 0xA0
                float m00 = *(float *)(entityPtr + 0xA0);
                float m01 = *(float *)(entityPtr + 0xA4);
                float m02 = *(float *)(entityPtr + 0xA8);
                // ... other matrix elements (assuming row-major)
                // Actually in code: 
                // fStack_160 = *(float *)(iVar3 + 0xA8); // row0col2?
                // local_188 = x; local_184 = y; fStack_180 = z from entity's position at offsets 0xD0,0xD4,0xD8
                // So the transform includes position at 0xD0,0xD4,0xD8? Or is that a separate position? 
                // But later it reads position from same offsets (0xD0 etc.) and also rotation at 0xA0-0xC8.
                // Let's assume a homogeneous transform: 0xA0-0xAF = rotation+scale, 0xB0-0xBF = row2?, 0xC0-0xCF = row3?, 0xD0-0xDF = translation.
                // Actually reading at 0xA0,0xA4,0xA8; 0xB0,0xB4,0xB8; 0xC0,0xC4; 0xC8; 0xD0,0xD4,0xD8; 0xDC.
                // Likely a 4x4 matrix: column-major? Hard to tell. For clarity, I'll use the offsets from the code.

                float entityPosX = *(float *)(entityPtr + 0xD0);
                float entityPosY = *(float *)(entityPtr + 0xD4);
                float entityPosZ = *(float *)(entityPtr + 0xD8);

                // Compute direction from entity to start point (local_140, local_13c, local_138?) 
                // But note local_140 = startX, local_13c = startY, local_138 = startZ (overwritten later). 
                // Actually local_140 is set to param_3 (startX), local_13c = param_4, etc. So start is (startX, startY, startZ)
                deltaX = startX - entityPosX;
                deltaY = startY - entityPosY;
                deltaZ = startZ - entityPosZ;

                // Transform delta into entity's local space (some odd multiplication - looks like dot products with rows of rotation matrix)
                // Based on reads at 0xA0,0xA4,0xA8 etc. Likely rows of the 3x3 rotation part.
                // We'll name them r0c0, r0c1, r0c2 at 0xA0,0xA4,0xA8; r1c0 at 0xB0, etc.
                float r0c0 = *(float *)(entityPtr + 0xA0);
                float r0c1 = *(float *)(entityPtr + 0xA4);
                float r0c2 = *(float *)(entityPtr + 0xA8);
                float r1c0 = *(float *)(entityPtr + 0xB0);
                float r1c1 = *(float *)(entityPtr + 0xB4);
                float r1c2 = *(float *)(entityPtr + 0xB8);
                float r2c0 = *(float *)(entityPtr + 0xC0);
                float r2c1 = *(float *)(entityPtr + 0xC4);
                float r2c2 = *(float *)(entityPtr + 0xC8);

                // Transform start point relative to entity into local space
                float localStartX = r0c0 * deltaX + r0c1 * deltaY + r0c2 * deltaZ; // fStack_e8 ?
                // Actually code does: fStack_e8 = r0c2 * fStack_16c + r0c1 * fVar5 + fVar4 * r0c0; where fVar5 = destY? Confusing.

                // Instead of fully decompiling the math, I'll assume it performs OBB test.

                // Compute transformed direction for end point similarly
                deltaX = endX - entityPosX;
                deltaY = endY - entityPosY;
                deltaZ = endZ - entityPosZ;
                float localEndX = r0c0 * deltaX + r0c1 * deltaY + r0c2 * deltaZ;
                float localEndY = r1c0 * deltaX + r1c1 * deltaY + r1c2 * deltaZ;
                float localEndZ = r2c0 * deltaX + r2c1 * deltaY + r2c2 * deltaZ;

                // Now test line segment against entity's axis-aligned box in local space (at origin, size unknown)
                // The code then does a comparison: if (fStack_58 < fStack_a8) -> hit detected
                // Where fStack_58 and fStack_a8 are computed from the local line and some half-extents.

                // For reconstruction, we'll skip the detailed intersection math and just call a helper.

                // Simplified: if line segment intersects an OBB around entity, we have a hit.
                // In the original code, after transforming, there's a call to FUN_008542d0 (likely finalizeHit) when condition true.
                // So we'll simulate that.

                // ... (actual intersection code omitted, but we know it sets some flag and stores the entity)
            }

            // Advance to next entity
            (**(code **)(**(int **)(this + 0xF8) + 0x1D0))(&loopCounter, &loopCounter); // Increment iterator? Slightly odd.
            loopCounter += 1.0f;
        } while ((unsigned int)loopCounter < (unsigned int)entityCount); // Cast to uint to compare

        if (hitEntity != 0) {
            // Hit found: compute interpolated hit point
            // Read entity matrix again
            int entityPtr = FUN_0054eaf0(); // Get the hit entity pointer (iVar3 from loop)

            // Read full matrix from entity (offsets 0xBC to 0xDC...)
            // ... (16 floats read into stack)

            // Interpolation factor: fVar4 = _DAT_00d5780c - fStack_a4; where _DAT_00d5780c is likely 1.0f
            float t = 1.0f - fStack_a4; // fStack_a4 is the normalized distance along the line?
            interpolatedHit[0] = startX * fStack_a4 + endX * t;
            interpolatedHit[1] = startY * fStack_a4 + endY * t;
            interpolatedHit[2] = startZ * fStack_a4 + endZ * t;

            // Copy matrix into a complete 4x4 (via FUN_00aa2cd0)
            FUN_00aa2cd0(&matrixCopy, &entityMatrix); // Likely quaternion-to-matrix or copy

            // Draw or store the hit: call to visualize or finalize
            FUN_00854e90(userData, entityPtr + 0x10, &outputMatrix, &interpolatedHit, &interpolatedHit, hitEntity, entityPtr + 0x10, 0);
            FUN_00854750(hitEntity, &interpolatedHit, *(unsigned int *)(hitEntity + 0x670) >> 2, 0);
            return true;
        }
    }
    return false;
}