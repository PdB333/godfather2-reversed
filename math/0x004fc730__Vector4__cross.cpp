// FUNC_NAME: Vector4::cross
void Vector4::cross(const float* other, float* result) const {
    // Cross product of this (x,y,z,w) and other (x,y,z,w) -> 3D cross product, w set to 0
    result[0] = this->y * other[2] - this->z * other[1];
    result[1] = this->z * other[0] - this->x * other[2];
    result[2] = this->x * other[1] - this->y * other[0];
    result[3] = 0.0f;
}