// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *outResult, float scalar) {
    // Scale the 4-component vector (this) by scalar and store into outResult
    outResult[0] = this[0] * scalar;  // multiply x component
    outResult[1] = this[1] * scalar;  // multiply y component
    outResult[2] = this[2] * scalar;  // multiply z component
    outResult[3] = this[3] * scalar;  // multiply w component
}