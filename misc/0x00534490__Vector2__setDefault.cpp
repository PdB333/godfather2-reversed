// FUNC_NAME: Vector2::setDefault

// 0x00534490: Initializes a 2D vector to default values.
// The function first zeroes the x and y fields, then retrieves a pointer to default values
// from a helper function (FUN_00534560) and copies them into this vector.
// The zeroing appears redundant as it is overwritten, but may be a safety measure or
// leftover from a previous implementation.
void __thiscall Vector2::setDefault(Vector2 *this)
{
    // Zero out the vector components
    this->x = 0.0f; // +0x00
    this->y = 0.0f; // +0x04

    // Temporary buffer for default value retrieval (12 bytes, but only 8 used)
    char defaultBuffer[12];

    // Get pointer to default vector (likely a static constant or constructed from a global)
    Vector2 *defaultVec = (Vector2 *)FUN_00534560(defaultBuffer);

    // Overwrite with the default values
    this->x = defaultVec->x; // +0x00
    this->y = defaultVec->y; // +0x04
}