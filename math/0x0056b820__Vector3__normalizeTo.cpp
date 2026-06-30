// FUNC_NAME: Vector3::normalizeTo
// Address: 0x0056b820
// Role: Normalize a 3D vector (src = this) and write result to output pointer.
// Uses constants: DAT_00e2cbe0 (likely 0.0f) for zero check, DAT_00e2b1a4 (likely 1.0f) for unit scale.
// If squared length <= epsilon, sets output to zero vector; otherwise scales to unit length.

void __thiscall Vector3::normalizeTo(float *out) const
{
    float fVar1; // temp component
    float lenSq; // squared length

    fVar1 = this->x;
    lenSq = fVar1 * fVar1 + this->y * this->y + this->z * this->z; // x^2 + y^2 + z^2

    float factor;
    if (lenSq <= DAT_00e2cbe0) {    // zero or near-zero threshold
        factor = 0.0f;
    }
    else {
        factor = DAT_00e2b1a4 / __SQRT(lenSq); // scale factor = desiredLength / actualLength
    }

    out[0] = this->x * factor;  // component * factor
    out[1] = this->y * factor;
    out[2] = this->z * factor;
}