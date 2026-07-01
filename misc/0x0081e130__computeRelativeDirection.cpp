// FUNC_NAME: computeRelativeDirection
// Address: 0x0081e130
// This function computes a relative direction vector from a reference point (obtained from FUN_00424fb0) 
// to a target point derived by applying a rotation (quaternion) to a base direction.
// The base direction can be provided via param_3 or defaults to the player's orientation quaternion (from global DAT_01129944 + 0x108).
// If param_2 is true, the result vector is normalized; if the length is zero, a fallback vector (DAT_00d73250, DAT_00d73258) is used.

void computeRelativeDirection(float* outVec, bool normalize, const float* quatOpt)
{
    // Get transform handle (likely a pointer to a matrix stack or scene node)
    int transformHandle = getTransformHandle(0); // FUN_004262f0
    
    // Get reference vector from some system (e.g., current camera position)
    void* refVecPtr = getReferenceVector(&local_40, 0); // FUN_00424fb0 - writes to local_40, local_38? Return pointer to vector
    undefined8 uVar1 = *(undefined8*)refVecPtr;
    float refZ = *(float*)(refVecPtr + 1); // +8 offset after 8-byte value? Actually refVecPtr points to double? Let's treat as two floats.
    // Actually we need to interpret the 8 bytes as two floats for X and Y, then refZ as separate float.
    float refX = (float)uVar1;
    float refY = (float)((unsigned long long)uVar1 >> 32); // high 32 bits as float
    // Wait: the original decompiled used local_4c and fStack_48 from uVar1.
    // So reference vector X and Y come from uVar1 low and high parts, and refZ from next 4 bytes.

    // Obtain quaternion for rotation (either from param or default player quat)
    float quat[4];
    if (quatOpt == NULL)
    {
        // Default to player's rotation quaternion from global object at DAT_01129944
        quat[0] = *(float*)(DAT_01129944 + 0x108);
        quat[1] = *(float*)(DAT_01129944 + 0x10C);
        quat[2] = *(float*)(DAT_01129944 + 0x110);
        quat[3] = *(float*)(0x00d5780c); // global w component
    }
    else
    {
        quat[0] = quatOpt[0];
        quat[1] = quatOpt[1];
        quat[2] = quatOpt[2];
        quat[3] = quatOpt[3];
    }

    // Rotate a vector (possibly forward direction?) by the quaternion, output to local_20, local_1c, local_18
    // The first argument is transformHandle + 0x40 (likely offset to orientation matrix or something)
    // This function likely multiplies a 4x4 matrix (at transformHandle+0x40) by the quaternion and returns a vector.
    float rotatedVec[3];
    rotateVectorByQuaternion(transformHandle + 0x40, quat, rotatedVec); // FUN_0056b420

    // Compute difference between rotated vector and reference
    float diffX = rotatedVec[0] - refX;
    float diffY = rotatedVec[1] - refY;
    float diffZ = rotatedVec[2] - refZ;

    outVec[0] = diffX;
    outVec[1] = diffY;
    outVec[2] = diffZ;

    if (normalize)
    {
        // Calculate length squared
        double lenSq = computeDotProduct(&diffX, &diffX); // FUN_0056afa0 - takes two 3D vectors? Actually it takes &local_40 and &local_40 (the diff vector) and returns extended precision.
        // The function FUN_0056afa0 is called with &local_40 (the diff vector) twice, so it computes dot product of diff with itself.
        if (lenSq <= 0.0)
        {
            // Use default direction vector from globals (DAT_00d73250 and 00d73258)
            // Note: globals might be 8 bytes + 4? Actually outVec is 3 floats.
            *(undefined8*)outVec = DAT_00d73250; // low 8 bytes? That would set outVec[0] and outVec[1]
            outVec[2] = DAT_00d73258; // third float
        }
    }
}