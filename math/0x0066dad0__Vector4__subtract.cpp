// FUNC_NAME: Vector4::subtract

void Vector4::subtract(const float* other, float* out) const {
    float thisY = this->v[1];
    float thisZ = this->v[2];
    float thisW = this->v[3];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];
    out[0] = this->v[0] - other[0];
    out[1] = thisY - otherY;
    out[2] = thisZ - otherZ;
    out[3] = thisW - otherW;
}