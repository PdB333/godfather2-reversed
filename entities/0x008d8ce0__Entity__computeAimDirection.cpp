// FUNC_NAME: Entity::computeAimDirection
// Function at 0x008d8ce0: Computes a world-space aim target/direction for an entity.
// Reads position and orientation to produce a direction vector, then adds world offset.
// Returns a pointer to the world position used for offset.

int __thiscall Entity::computeAimDirection(Entity* thisObj, float* outVector)
{
    // Local 12-byte orientation quaternion or rotation matrix (3 floats)
    // Actually a 3D vector representing local forward/right?
    float orientation[3]; // local_50[12] but as floats? Actually 12 bytes = 3 floats
    // The decompiler shows undefined1[12] which is byte array, but we'll treat as 3 floats.
    // Ghidra's decompiler might mis-type; likely it's a float[3].

    // double? but used as two floats
    uint64 tempDouble; // local_60, used as two uint32s for float
    float tempY; // local_58, saved z component after rotation
    uint32 tempInt; // local_54, unused?
    uint32 constantZero[4] = {0,0,0,0}; // local_44, local_34, local_24, local_14 (but local_14 = _DAT_00d5780c)
    // Actually local_14 is set to _DAT_00d5780c (some constant)
    // We'll skip those as they appear unused or are local stack junk.

    // Get initial direction: x from offset 0x208, y=0, z from offset 0x238
    float fVar3 = *(float*)((uint8*)thisObj + 0x208);
    outVector[1] = 0.0f;
    outVector[0] = fVar3;
    outVector[2] = *(float*)((uint8*)thisObj + 0x238);

    // Get orientation data (likely from some component)
    // FUN_00470f80 probably fills orientation[3] with e.g. forward vector or rotation axis.
    // Assuming it's a function like getLocalForwardVector.
    FUN_00470f80(orientation); // orientation is a 3-float vector?

    // Compute magnitude of original direction
    float magnitude = sqrtf(outVector[0]*outVector[0] + outVector[1]*outVector[1] + outVector[2]*outVector[2]);

    // Apply orientation rotation to the direction vector (outVector becomes rotated direction)
    // FUN_006cb9d0 likely rotates vector by orientation.
    // Prototype: void rotateVector(float* out, float* in, float* rotationMatrix)
    FUN_006cb9d0(outVector, outVector, orientation);

    // Save z component after rotation, then set y to 0
    tempY = outVector[2];
    outVector[1] = 0.0f;

    // Extract the x component's float bits as uint32, then zero-extend to uint64
    // This is a reinterpret cast to get the bits for input to a function.
    uint32 xBits = *(uint32*)&outVector[0]; // direct bit copy
    tempDouble = (uint64)xBits; // zero extended

    // Call function to convert (x,0) to polar or compute sin/cos?
    // FUN_0056afa0 likely takes a pointer to two floats (x and y, though y is zero) and returns angle components.
    // Actually it modifies tempDouble which holds two floats in low and high 32 bits.
    FUN_0056afa0(&tempDouble, &tempDouble); // in-place

    // Reconstruct direction from polar components and scale by original magnitude
    // tempDouble low 32 bits = some float, high 32 bits = another float (maybe cos and sin?)
    outVector[0] = *(float*)&tempDouble * magnitude;
    outVector[1] = *(((float*)&tempDouble) + 1) * magnitude; // second float in the 8-byte block
    outVector[2] = tempY * magnitude; // restore z and scale

    // Get world position offset from some global manager
    // FUN_00471610 likely returns a pointer to a WorldData structure (e.g., CameraManager or LevelInfo)
    int worldDataPtr = FUN_00471610();
    // Read world position offset (x, y, z) from +0x30 and +0x38
    uint64 offsetXY = *(uint64*)(worldDataPtr + 0x30); // two floats packed
    float offsetZ = *(float*)(worldDataPtr + 0x38);

    // Extract world x and y from the double (as two floats)
    float offsetX = *(float*)&offsetXY;
    float offsetY = *(((float*)&offsetXY) + 1);

    // Add world offset to computed direction
    outVector[0] += offsetX;
    outVector[1] += offsetY;
    outVector[2] += offsetZ;

    // Return pointer to the offset source (world position)
    return worldDataPtr + 0x30;
}