// FUNC_NAME: applyGravityToPosition
void applyGravityToPosition(Vector3* outPosition)
{
    // Retrieve pointer to entity data (likely the player or an object)
    int entityPtr = FUN_00471610(); // e.g., getActiveEntity()
    
    // Copy x and y from entity position (two floats at +0x30)
    // +0x30: local position x, y (8 bytes, likely Vector2)
    *reinterpret_cast<Vector2*>(outPosition) = *reinterpret_cast<Vector2*>(entityPtr + 0x30);
    
    // Add gravity delta to y component
    float gravityDelta = static_cast<float>(FUN_006c55d0()); // gravity or vertical offset
    outPosition->y += gravityDelta;
    
    // Copy z from entity +0x38
    // +0x38: local position z (4 bytes)
    outPosition->z = *reinterpret_cast<float*>(entityPtr + 0x38);
}