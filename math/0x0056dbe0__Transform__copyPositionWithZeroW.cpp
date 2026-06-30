// FUNC_NAME: Transform::copyPositionWithZeroW
// Copies a 4-component vector from source->position (+0x30) to dest->someVector (+0x10), then zeros the W component.
// This is used to convert a position vector (with arbitrary W) to a directional vector (W=0) or to clear the 4th component.
// Source and destination are assumed to be Transform or Entity objects with vector fields at these offsets.
// +0x30: Vector4 position (x, y, z, w)
// +0x10: Vector4 someVector (x, y, z, w) -- likely a local direction or target vector

void Transform::copyPositionWithZeroW(Transform* dest) {
    // Call base copy function (likely copies a larger structure like a matrix or transform)
    // FUN_0056d530 may copy 16 bytes from param_1 to param_2, possibly a quaternion or rotation data
    Transform::copyBase(dest);   // FUN_0056d530

    // Copy the position vector (4 floats) from source (+0x30) to dest's target vector (+0x10)
    dest->someVector.x = this->position.x;
    dest->someVector.y = this->position.y;
    dest->someVector.z = this->position.z;
    dest->someVector.w = this->position.w;

    // Zero out the W component (converts to a 3D direction vector or ensures not used)
    dest->someVector.w = 0.0f;
}