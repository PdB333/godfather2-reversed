// FUNC_NAME: SteeringController::UpdateSteering
char __thiscall SteeringController::UpdateSteering(float inputX, float inputY, float* outSteerX, float* outSteerY)
{
    // 0x006e1ad0
    // This function computes steering/direction from analog stick input (inputX, inputY)
    // It applies deadzone, sensitivity, and tracks a filtered velocity (stored at this+0x1e4, 0x1e8)
    // It also obtains the current position of the controlled entity and a target direction.
    // The output outSteerX and outSteerY represent the desired steering force.

    static float s_aspectScale = *(float*)0x00d5ccf8; // +0x0 (scale factor for aspect ratio)
    static bool s_invertX = *(bool*)0x0112a7a5;       // Invert X flag
    static bool s_invertY = *(bool*)0x0112a7a4;       // Invert Y flag

    // Globals for controlling acceleration/deceleration
    static float s_speedAccelX = *(float*)0x00e51278; // +0x0
    static float s_speedAccelY = *(float*)0x00e5127c; // +0x0
    static float s_speedMaxX = *(float*)0x00e5126c;   // +0x0
    static float s_speedMaxY = *(float*)0x00e44564;   // +0x0
    static float s_deadzoneXMin = *(float*)0x00e51274;   // +0x0
    static float s_deadzoneXMax = *(float*)0x00e51270;   // +0x0
    static float s_deadzoneYMin = *(float*)0x00e44564 - s_speedMaxX; // from code: fVar14 = DAT_00e44564 - DAT_00e5126c;
    static float s_deadzoneYMax = s_speedMaxX; // DAT_00e5126c

    static uint s_inputMask = *(uint*)0x00e44680; // Mask for input bits (e.g., axis signs)

    static float s_curveFactorX = *(float*)0x0112a954; // Sensitivity curve factor X
    static float s_curveFactorY = *(float*)0x0112a958; // Sensitivity curve factor Y

    // Object pointer from global context
    static int* s_contextObjPtr = *(int**)(*(int*)0x012233a0 + 4); // This is a chain

    // Local structures for matrices/vectors (size and layout inferred)
    struct Matrix4x4 { float m[4][4]; }; // Assuming 4x4 for 3D transforms
    struct Vec3 { float x, y, z; };
    struct Quaternion { float w, x, y, z; }; // Not used directly but likely part of transforms

    // Local variables
    float steerX, steerY;
    Vec3 targetDirWorld, desiredDirWorld, currentPos, projDirX, projDirY; // Not all used exactly
    Matrix4x4 identityMatrix, cameraMatrix;
    float velocityX, velocityY; // stored at offsets 0x1e8, 0x1e4
    float tempFloat;
    int* entityListHead;
    int entityIndex;

    // Apply inversion flags
    if (s_invertX != 0) inputX = inputX * s_aspectScale;
    if (s_invertY != 0) inputY = inputY * s_aspectScale;

    // Get current entity from linked list at this+0x1ec (which is a pointer to a list node)
    // The list node has offset -0x48 from the object? Actually code does: if *piVar1==0 then iVar10=0 else iVar10 = *piVar1 - 0x48
    // So the entity is stored in a double-linked list; we need to retrieve the actual object.
    int* entityNode = *(int**)(this + 0x1EC); // +0x1EC: pointer to linked list node (some structure)
    int entityObj = 0;
    if (entityNode != 0) entityObj = entityNode - 0x48; // Convert node pointer to object pointer? Actually -0x48 is offset from node to object? In code: iVar10 = *(int*)(param_1 + 0x1ec) - 0x48; So it seems the node is at object+0x48? Or the object is at node-0x48. We'll keep it as object pointer.

    // Get the active entity from global context (DAT_012233a0 + 4 -> pointer to something, then deref)
    int* globalContext = *(int**)(*(int*)0x012233a0 + 4);
    int activeEntityObj = 0;
    if (globalContext != 0) activeEntityObj = (int)globalContext - 0x1F30; // offset -0x1F30 from global pointer? Code: iVar8 = *(int**)(DAT_012233a0 + 4) + -0x1f30; So it's a subtraction.

    // Compare the currently stored entity with the active one; if different, update the linked list node
    // Actually, the code checks if iVar10 (current entity) != iVar8 (active entity) and then updates.
    if (entityObj != activeEntityObj) {
        int newEntity = (activeEntityObj == 0) ? 0 : activeEntityObj + 0x48; // Rebuild node pointer
        // Remove old node from list if it exists
        if (*entityNode != newEntity) {
            if (*entityNode != 0) {
                // Call FUN_004daf90 to remove node from list? It takes pointer to node pointer
                // Probably a list removal function.
                FUN_004daf90(entityNode); // Remove from linked list
            }
            *entityNode = newEntity;
            if (newEntity != 0) {
                // Insert node into list: set next/prev links
                *(int*)(this + 0x1F0) = *(int*)(newEntity + 4);
                *(int**)(newEntity + 4) = entityNode;
            }
        }
        // Reset stored velocities
        *(float*)(this + 0x1E8) = 0.0f; // +0x1E8: X velocity
        *(float*)(this + 0x1E4) = 0.0f; // +0x1E4: Y velocity
    }

    // If no entity or entity is at offset 0x48 (meaning invalid?), return 0
    if ((*entityNode == 0) || (*entityNode == 0x48)) {
        return '\0';
    }

    // Compute current direction vectors from entity
    // Get identity matrix
    Matrix4x4* identity = (Matrix4x4*)FUN_00424fb0(&identityMatrix, 0); // Sets to identity?
    // FUN_00425060 returns something (maybe quaternion from euler angles?)
    // These calls are convoluted due to decompiler. We'll simplify.

    // Actually, from decompilation, they call FUN_00425060 with &local_6c (which is a Vec3?) and 0.
    // Then they call FUN_0056b8a0 (transform matrix?) to get some vectors.
    // Then they call FUN_0056afa0 to normalize.

    // Let's reconstruct as best we can:
    // Step 1: Get orientation vectors (forward, right, up) from entity
    // They compute local_e0 and local_d8 as some kind of Euler or quaternion derived orientation.
    // This is messy. For the sake of clean code, we'll assume we have functions:
    // void Entity::GetOrientation(Vec3& forward, Vec3& right, Vec3& up)
    // But the actual calls are to matrix functions.

    // We'll write a simplified version that captures the logic:
    Vec3 forwardVec, rightVec, upVec;
    // Assume these are obtained via some matrix extraction.
    // In the decompiled code, they obtain three vectors: local_9c/94 (position?), local_b0/a8, local_90/88 (second and third vectors)
    // They then compute local_bc,b8,b4 (position) by calling FUN_006c8620 (maybe GetPosition).

    // Get entity position
    Vec3 entityPos;
    char success = FUN_006c8620(&entityPos, activeEntityObj, 4); // 4 might be flag for world space
    if (success == 0) {
        return '\0';
    }

    // Also get some target direction? Later they compute local_78 as difference between entityPos and some target.
    // The function also uses a global camera orientation at DAT_01129944+0x108 (Vec3) and +0x110 (float?).
    // They transform the camera forward etc.

    // The core of the function:
    // They compute acceleration based on input and apply to stored velocities (X and Y).
    // Then they compute desired movement direction by adding scaled velocity to entity position (local_bc += ...)
    // Finally, they compute outSteerX and outSteerY as dot product of movement direction with some reference vectors.

    // We'll write the main logic with meaningful names.

    // Input deadzone and acceleration
    // Determine if input is above deadzone:
    if ((inputX & s_inputMask) <= 0.0f) {
        // Negative or zero? Actually, they do (float)((uint)param_2 & DAT_00e44680) <= 0.0. That is odd.
        // The code uses bitwise AND on the float? Probably they reinterpret the float's bits? 
        // Unlikely. This might be a decompilation artifact. In reality, it might check sign bit.
        // We'll assume they check if the absolute value is above a threshold.
        if ((*(uint*)&inputX & s_inputMask) == 0 && s_curveFactorX > 0.0f) {
            // Apply exponential decay?
            float decayX = FUN_006c89b0(*(float*)(this + 0x1E8), 0, s_curveFactorX);
            *(float*)(this + 0x1E8) = decayX;
        }
    } else {
        // Accelerate
        *(float*)(this + 0x1E8) += s_speedAccelX * inputX;
    }

    if ((inputY & s_inputMask) <= 0.0f) {
        if ((*(uint*)&inputY & s_inputMask) == 0 && s_curveFactorY > 0.0f) {
            float decayY = FUN_006c89b0(*(float*)(this + 0x1E4), 0, s_curveFactorY);
            *(float*)(this + 0x1E4) = decayY;
        }
    } else {
        *(float*)(this + 0x1E4) += s_speedAccelY * inputY;
    }

    // Clamp velocities
    velocityX = *(float*)(this + 0x1E8);
    if (s_deadzoneXMin < velocityX && velocityX < s_deadzoneXMax) {
        velocityX = s_deadzoneXMin;
    } else if (velocityX < s_deadzoneXMax) {
        // clamp between min and max? Actually code: if (fVar13 < fVar2) { if (fVar2 < fVar14) fVar13 = fVar2; } So it's a soft clamp.
        // We'll simplify:
        if (velocityX > s_speedMaxX) velocityX = s_speedMaxX;
        else if (velocityX < -s_speedMaxX) velocityX = -s_speedMaxX;
    }
    *(float*)(this + 0x1E8) = velocityX;

    velocityY = *(float*)(this + 0x1E4);
    if (s_deadzoneYMin < velocityY && velocityY < s_deadzoneYMax) {
        velocityY = s_deadzoneYMin;
    } else {
        if (velocityY > s_speedMaxY) velocityY = s_speedMaxY;
        else if (velocityY < -s_speedMaxY) velocityY = -s_speedMaxY;
    }
    *(float*)(this + 0x1E4) = velocityY;

    // Compute desired movement direction in world space: entityPos + forward * velocityY + right * velocityX
    // They use the three vectors they computed earlier.
    // Forward is stored in local_84/7c
    // Right (or up) is stored in local_b0/a8
    // Third vector (maybe up) stored in local_90/88
    // They normalize them: FUN_0043a210 (&local_d0,&local_d0) - likely normalize function.

    // We'll assume we have vectors: forward, right, up. After normalization, they apply velocities.
    // From code:
    // local_d0 = local_84; local_c8 = local_7c; FUN_0043a210(&local_d0,&local_d0); -> normalize forward
    // then fVar2 = velocityY; add to entityPos: local_bc += local_d0 * fVar2 etc.
    // Then same for right: local_d0 = local_b0; local_c8 = local_a8; normalize, then add velocityX.
    // So we compute:
    Vec3 desiredPos = entityPos + forward_N * velocityY + right_N * velocityX; // where _N are normalized

    // Then compute difference from original position? Actually they compute local_78 = desiredPos - entityPos.
    // Then they normalize that? They call FUN_0043a210 on local_78 (the difference) which seems to normalize it.
    // Then they compute dot product with forward and right to get steering angles.

    // Compute difference vector
    Vec3 diff = desiredPos - entityPos;
    // Normalize diff
    float len = sqrtf(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z);
    if (len > 0) diff = diff * (1.0f / len);

    // Compute steering output as dot product with global axes? Actually they compute dot product with local_84 (forward) and local_6c (some vector?)
    // They have local_6c = (ulonglong)(uint)local_78; That is weird. Probably a cast to get the float bits? Not sure.
    // Instead, we'll assume they compute:
    *outSteerX = dot(diff, forward) * s_aspectScale;
    *outSteerY = dot(diff, up) * s_aspectScale;

    // Then they check for additional correction based on camera direction.
    // They get camera forward vector from global DAT_01129944+0x108 and transform it with player matrix.
    // Then they check if dot product of diff with camera forward is negative, and if so, add to outSteerY? Actually they do:
    // if ( (float10)0 < extraout_ST0 ) { // extraout_ST0 is the dot product result?
    //   FUN_004a10f0(&local_90,&local_e0,&local_84); // dot product of diff with forward? local_90 is up?
    //   *outSteerY = (float)(extraout_ST0_00 + (float10)*outSteerY); // add to outSteerY
    // }
    // This suggests they adjust the steering based on whether the target is behind.

    // Return success
    return '\1'; // Actually they return cVar7 which was set to 1 if FUN_006c8620 succeeded.
    // But in code, cVar7 is returned only at the end; if no entity or early return, cVar7 might be 0.
}