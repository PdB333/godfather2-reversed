// FUNC_NAME: Entity::updateWorldPosition
// Computes world transform matrix and stores translation to position field at +0x10, +0x14, +0x18
void __thiscall Entity::updateWorldPosition()
{
    float worldMatrix[12]; // 48 bytes, 3x4 row-major transform matrix
    // Update global state (e.g., engine tick)
    FUN_00424470();
    // Update time (e.g., delta time)
    FUN_00417560();
    // Compute world transform: likely multiply local transforms up the hierarchy
    FUN_0056d530(worldMatrix);
    // Extract translation (column 3) from matrix and store as position
    *(float*)(this + 0x10) = worldMatrix[3];   // x
    *(float*)(this + 0x14) = worldMatrix[7];   // y
    *(float*)(this + 0x18) = worldMatrix[11];  // z
}