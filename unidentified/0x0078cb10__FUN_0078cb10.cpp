// FUNC_NAME: SomeClass::computeTargetPosition
// Address: 0x0078cb10
// This function computes a target position along a line from one entity to another,
// rotated by the second entity's orientation, and interpolated by a factor.
// It also manages a state machine based on flags at +0x20 and a timer at +0x1c.

int __thiscall SomeClass::computeTargetPosition(float factor, int unused, float* outPosition)
{
    int state = 0;
    float* thisPtr = this; // param_1

    // Check timer and reset if expired
    if (*(float*)(thisPtr + 0x1c) <= kTimeThreshold && kTimeThreshold != *(float*)(thisPtr + 0x1c)) {
        *(byte*)(thisPtr + 0x20) = 0;
        *(float*)(thisPtr + 0x1c) = 0.0f;
    }

    // State machine based on flags at +0x20
    if ((*(byte*)(thisPtr + 0x20) & 8) == 0) {
        state = 3;
    } else {
        if (*(float*)(thisPtr + 0x1c) <= kTimeThreshold && kTimeThreshold != *(float*)(thisPtr + 0x1c)) {
            *(byte*)(thisPtr + 0x20) = 0;
            *(float*)(thisPtr + 0x1c) = 0.0f;
        }
        if ((*(byte*)(thisPtr + 0x20) & 0x10) == 0) {
            state = 4;
        } else {
            if (*(float*)(thisPtr + 0x1c) <= kTimeThreshold && kTimeThreshold != *(float*)(thisPtr + 0x1c)) {
                *(byte*)(thisPtr + 0x20) = 0;
                *(float*)(thisPtr + 0x1c) = 0.0f;
            }
            if ((*(byte*)(thisPtr + 0x20) & 0x20) == 0) {
                state = 5;
            }
        }
    }

    // Get two entity pointers (likely source and target)
    int entity1 = getSomeEntity(); // FUN_00471610
    int entity2 = getSomeEntity(); // FUN_00471610

    // Compute direction from entity1 to entity2 (only X and Z used, Y = 0)
    float dirX = *(float*)(entity2 + 0x30) - *(float*)(entity1 + 0x30);
    float dirY = 0.0f;
    float dirZ = *(float*)(entity2 + 0x38) - *(float*)(entity1 + 0x38);

    // Normalize the direction vector
    Vector3 dir = { dirX, dirY, dirZ };
    vectorNormalize(&dir, &dir); // FUN_0056afa0

    // Get a rotation value based on state
    float rotation = getRotationAngle(state); // FUN_0078c2a0

    // Get the second entity's transform matrix (at +0x10)
    int transformMatrix = entity2 + 0x10;

    // Rotate the direction by the entity's orientation matrix
    Vector3 rotatedDir;
    transformVectorByMatrix(&rotatedDir, &dir, transformMatrix); // FUN_004a0370

    // Compute final position: entity1 origin + factor * rotated direction
    outPosition[0] = rotatedDir.x * factor + *(float*)(entity1 + 0x30);
    outPosition[1] = rotatedDir.y * factor + *(float*)(entity1 + 0x34);
    outPosition[2] = rotatedDir.z * factor + *(float*)(entity1 + 0x38);

    return state;
}