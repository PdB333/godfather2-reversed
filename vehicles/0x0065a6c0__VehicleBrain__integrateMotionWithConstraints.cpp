// FUNC_NAME: VehicleBrain::integrateMotionWithConstraints
// Function at 0x0065A6C0: Applies linear displacement to physics object position, copies rotation matrix from offset +0x6C, and calls constraint solver (FUN_00661210). Clears flag at +0x270.

#include <malloc.h>

void __thiscall VehicleBrain::integrateMotionWithConstraints(float deltaX, float deltaY, float deltaZ)
{
    // Allocate temporary buffer for rotation matrix copy (0x204 bytes = 129 floats)
    float* rotationMatrixCopy = (float*)_alloca(0x204);

    // Update position (float3 at +0x0C) by adding delta to previous position (float3 at +0x1C)
    // Offsets: +0x0C = position.x, +0x10 = position.y, +0x14 = position.z
    //          +0x1C = previousPosition.x, +0x20 = previousPosition.y, +0x24 = previousPosition.z
    *(float*)(this + 0x0C) = *(float*)(this + 0x1C) + deltaX;
    *(float*)(this + 0x10) = *(float*)(this + 0x20) + deltaY;
    *(float*)(this + 0x14) = *(float*)(this + 0x24) + deltaZ;

    // Copy rotation matrix from +0x6C to local buffer
    float* src = (float*)(this + 0x6C);
    for (int i = 0; i < 0x81; i++)
    {
        rotationMatrixCopy[i] = src[i];
    }

    // Store previous orientation at +0x18 from value at +0x28
    *(float*)(this + 0x18) = *(float*)(this + 0x28);

    // Call constraint solver with new position, data at +0x5C, and copied matrix
    FUN_00661210(this + 0x0C, this + 0x5C, rotationMatrixCopy);

    // Clear flag at +0x270
    *(int*)(this + 0x270) = 0;
}