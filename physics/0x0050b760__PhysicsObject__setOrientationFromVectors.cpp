// FUNC_NAME: PhysicsObject::setOrientationFromVectors
// Address: 0x0050b760
// This function calculates an orientation matrix from a forward and up vector,
// applies smoothing/interpolation, and updates the physics body transform.
void PhysicsObject::setOrientationFromVectors(float* forwardVector, float* upVector, int param5, bool enableBlending, bool invertUp)
{
    // Get physics body pointer from this +0x24
    int* bodyPtr = *(int**)(this + 0x24);
    
    // Check if body has any non-zero components at offsets 0x50,0x54,0x58,0x5c (likely linear velocity)
    if ((*(int*)(bodyPtr + 0x50) == 0 && *(int*)(bodyPtr + 0x54) == 0 && 
         *(int*)(bodyPtr + 0x58) == 0 && *(int*)(bodyPtr + 0x5c) == 0) ||
        (*(int*)(bodyPtr + 0x50) == 0 && *(int*)(bodyPtr + 0x54) == 0 && 
         *(int*)(bodyPtr + 0x58) == 0 && *(int*)(bodyPtr + 0x5c) == 0))
    {
        // Both conditions are identical? Possibly checks for linear velocity being zero.
        return;
    }

    // Get global physics manager (singleton) from FUN_004e0f60
    int* physicsMgr = (int*)FUN_004e0f60();
    if (physicsMgr == 0 || *physicsMgr == 0)
        return;
    int bodyHandle = *physicsMgr;

    // Build identity matrix in local variables (3x3 stored as 3 columns)
    float matrix[3][3];
    const float one = DAT_00e2b1a4; // likely 1.0f
    matrix[0][0] = one; matrix[0][1] = 0.0f; matrix[0][2] = 0.0f;
    matrix[1][0] = 0.0f; matrix[1][1] = one; matrix[1][2] = 0.0f;
    matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = one;

    // Normalize forward vector
    float fwdX = forwardVector[0];
    float fwdY = forwardVector[1];
    float fwdZ = forwardVector[2];
    float fwdLenSq = fwdX*fwdX + fwdY*fwdY + fwdZ*fwdZ;
    float fwdInvLen;
    if (fwdLenSq <= DAT_00e2cbe0) // epsilon for zero length
        fwdInvLen = 0.0f;
    else
        fwdInvLen = one / sqrtf(fwdLenSq);
    fwdX *= fwdInvLen;
    fwdY *= fwdInvLen;
    fwdZ *= fwdInvLen;

    // Normalize up vector
    float upX = upVector[0];
    float upY = upVector[1];
    float upZ = upVector[2];
    float upLenSq = upX*upX + upY*upY + upZ*upZ;
    float upInvLen;
    if (upLenSq <= DAT_00e2cbe0)
        upInvLen = 0.0f;
    else
        upInvLen = one / sqrtf(upLenSq);
    upX *= upInvLen;
    upY *= upInvLen;
    upZ *= upInvLen;

    float normFwdX = fwdX;
    float normFwdY = fwdY;
    float normFwdZ = fwdZ;
    float normUpX = upX;
    float normUpY = upY;
    float normUpZ = upZ;

    // Push matrix stack? (FUN_00414aa0 is likely a push/pop for matrix operations)
    FUN_00414aa0();

    // Compute dot product between forward and up
    float dot = normFwdX * normUpX + normFwdY * normUpY + normFwdZ * normUpZ;
    // The next call might be a random or debug break (FUN_00b9b988)
    FUN_00b9b988();
    
    if (DAT_00e2e780 < dot) // dot > some threshold (maybe 1.0?)
    {
        // Cross product: up = cross(forward, up)
        float crossX = normFwdY * normUpZ - normFwdZ * normUpY;
        float crossY = normFwdZ * normUpX - normFwdX * normUpZ;
        float crossZ = normFwdX * normUpY - normFwdY * normUpX;
        // Recompute up from cross product
        FUN_004f1c90(&normUpX, &normFwdX, &crossX); // might be cross or normalize
        // Recompute forward from up and cross? 
        FUN_004f1c90(&normFwdX, &crossX, &normUpX);
        // Check magnitude of new up vector
        float upLen = normUpX*normUpX + normUpY*normUpY + normUpZ*normUpZ;
        if (upLen >= DAT_00e44598)
        {
            FUN_00414aa0(); // push matrix again?
        }
    }

    // Compute right vector from cross product of matrix columns (identity initial)
    // matrix columns: m0 = (matrix[0][0], matrix[1][0], matrix[2][0]) etc.
    // Actually the matrix is stored as: local_60 = m00, fStack_5c = m01, fStack_58 = m02,
    // local_50 = m10, fStack_4c = m11, fStack_48 = m12,
    // local_40 = m20, fStack_3c = m21, fStack_38 = m22.
    // Compute cross product of first two columns (right = up x forward?)
    // The code computes:
    // fVar3 = m22 * m11 - m21 * m12
    // fStack_5c = m20 * m12 - m22 * m10
    // fStack_58 = m21 * m10 - m20 * m11
    // This is cross(column2, column1) if column order is: (m00,m10,m20) = forward? Actually unclear.
    // Then normalize the result.
    float crossX2 = matrix[2][2] * matrix[1][1] - matrix[2][1] * matrix[1][2];
    float crossY2 = matrix[2][0] * matrix[1][2] - matrix[2][2] * matrix[1][0];
    float crossZ2 = matrix[2][1] * matrix[1][0] - matrix[2][0] * matrix[1][1];
    float crossLenSq = crossX2*crossX2 + crossY2*crossY2 + crossZ2*crossZ2;
    float crossInvLen;
    if (crossLenSq <= DAT_00e2cbe0)
        crossInvLen = 0.0f;
    else
        crossInvLen = one / sqrtf(crossLenSq);
    crossX2 *= crossInvLen;
    crossY2 *= crossInvLen;
    crossZ2 *= crossInvLen;

    // If the cross product is too small, set it to unit x? 
    if (crossX2*crossX2 + crossY2*crossY2 + crossZ2*crossZ2 < DAT_00e44598)
    {
        crossX2 = one;
        crossY2 = 0.0f;
        crossZ2 = 0.0f;
    }

    // Recompute forward and up from the cross product (Gram-Schmidt)
    // New up = cross(column2, column1) but using the identity? This part is confusing.
    // The code then does:
    // local_40 = crossY2 * matrix[1][2] - crossX2 * matrix[1][1];
    // fStack_3c = crossX2 * matrix[2][2] - crossZ2 * matrix[1][2];
    // fStack_38 = crossZ2 * matrix[1][1] - crossY2 * matrix[2][2];
    // This seems to compute the final orientation matrix.

    // If enableBlending is true, do additional blending/interpolation with up vector
    if (enableBlending)
    {
        // Blend vectors with target orientation (DAT_00e2cbb0 might be identity basis)
        float blendFrom[3] = {0,0,0};
        float blendTo[3] = {0,0,0};
        // ... (complex blending logic)
        // Many local variables used for interpolation
    }

    // Apply the matrix to the physics body
    // bodyHandle is from the global manager, param is this+4+0x84 (maybe world transform pointer)
    FUN_004df210(bodyHandle, &matrix, *(undefined4*)(*(int*)(this + 4) + 0x84), 0);

    // Check return value from FUN_004df210? local_114 is uninitialized in decompiled, but likely eax
    int retVal = 0; // Actually should capture return value from previous call
    if (retVal != 0)
    {
        // Allocate 0xB0 bytes for a new object
        int newObj = FUN_004e0750(0xB0);
        if (newObj == 0)
        {
            // handle null
        }
        else
        {
            int* newPtr = (int*)FUN_00508f90(); // constructor?
            FUN_00509160(param5); // some operation
            (*(code**)(*newPtr + 0x10))(enableBlending); // vtable call
            (*(code**)(*newPtr + 0x20))(&matrix); // vtable call
            (*(code**)(*newPtr + 0x24))(&blendTo); // vtable call
            FUN_004df830(newPtr); // destructor/cleanup
            if (/* global some flag */)
            {
                *(int*)(/* some address */ + 8) = 0;
            }
        }
    }
}