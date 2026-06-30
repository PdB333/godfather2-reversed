// FUNC_NAME: VectorInterpolator::lerpTo
void __thiscall VectorInterpolator::lerpTo(float *from, float *to, float t, float *out) {
    // Interpolates from vector to vector with factor scaled by internal blend speed
    // this +0x60: interpolationScale (speed factor)
    float yFrom = from[1];
    float zFrom = from[2];
    float yTo = to[1];
    float zTo = to[2];
    
    // Apply internal scaling to interpolation factor
    t = *(float *)(this + 0x60) * t;
    
    // Linear interpolation on each component
    out[0] = from[0] + (to[0] - from[0]) * t;   // X
    out[1] = yFrom + (yTo - yFrom) * t;          // Y
    out[2] = zFrom + (zTo - zFrom) * t;          // Z
}