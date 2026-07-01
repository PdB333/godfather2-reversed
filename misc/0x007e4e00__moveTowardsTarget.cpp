// FUNC_NAME: moveTowardsTarget
// Function address: 0x007e4e00
// Role: Moves an entity from currentPosition towards a target position, using a direction vector and a speed factor.
// The target position is obtained via a virtual function call on targetObject (vtable offset 0xa4).
// The speed factor is multiplied by a global constant (_DAT_00e53420) and the distance to target.
// Then calls FUN_004a08d0 to apply the movement.

void moveTowardsTarget(void* entity, float* currentPosition, float* direction, void* targetObject)
{
    float diff[3]; // difference vector from current to target
    float length;
    float newPosition[3];

    // Call virtual function at vtable offset 0xa4 (likely getTargetPosition)
    // Second argument is targetObject + 0x1c0 (some internal data)
    (**(void (__thiscall**)(void*, float*, void*))(*(int*)targetObject + 0xa4))(targetObject, diff, (char*)targetObject + 0x1c0);

    // Compute difference from current position to target
    diff[0] -= currentPosition[0];
    diff[1] -= currentPosition[1];
    diff[2] -= currentPosition[2];

    // Compute distance scaled by global speed constant
    length = sqrt(diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2]) * _DAT_00e53420;

    // Compute new position along direction vector
    newPosition[0] = currentPosition[0] + direction[0] * length;
    newPosition[1] = currentPosition[1] + direction[1] * length;
    newPosition[2] = currentPosition[2] + direction[2] * length;

    // Apply movement (likely sets new velocity or position)
    FUN_004a08d0(entity, diff, currentPosition, newPosition);
}