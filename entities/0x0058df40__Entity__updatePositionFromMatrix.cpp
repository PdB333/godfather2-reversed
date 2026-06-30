//FUNC_NAME: Entity::updatePositionFromMatrix
void __thiscall Entity::updatePositionFromMatrix(void)
{
    // Local buffer for a 3x4 transformation matrix (12 floats = 48 bytes)
    float matrix[12]; // [0x0] - [0x2C]

    // Call helper functions (likely update internal state or compute something)
    FUN_00424470(); // unknown: maybe preUpdate()
    FUN_00417560(); // unknown: maybe computeMatrix()

    // Fill the matrix from some source (e.g., animation or physics)
    FUN_0056d530(matrix); // fills matrix[12] with transformation data

    // Extract translation (position) from matrix columns 3, 7, 11 (last column of 3x4)
    // Offsets +0x10, +0x14, +0x18 correspond to position vector in this object
    *(float *)(this + 0x10) = matrix[3];  // x
    *(float *)(this + 0x14) = matrix[7];  // y
    *(float *)(this + 0x18) = matrix[11]; // z
}