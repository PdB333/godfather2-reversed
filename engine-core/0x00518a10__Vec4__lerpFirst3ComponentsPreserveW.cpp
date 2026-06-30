// FUNC_NAME: Vec4::lerpFirst3ComponentsPreserveW
// Reconstructed C++: Linear interpolation for first three components of a 4D vector, preserving the fourth component.
// This is typical for blending positions (x,y,z) while leaving a weight or rotation (w) unchanged.
// The function signature is __thiscall; the object pointed to by ECX (in_EAX) is the output.
void __thiscall Vec4::lerpFirst3ComponentsPreserveW(float *from, float *to, float mix) {
    // from and to are float[4] pointers (x,y,z,w)
    // mix: interpolation factor, typically in [0,1]
    // The function writes to this object's first three components: x = mix*from.x + to.x, etc.
    // W component is left unchanged (original value preserved).

    float fX = from[0];   // +0x00
    float fY = from[1];   // +0x04
    float fZ = from[2];   // +0x08
    float fW = from[3];   // +0x0C (w of 'from', computed but not used in final output)

    // Save original w of the output object (this->w)
    float originalW = this->w; // +0x0C

    float tX = to[0];     // +0x00
    float tY = to[1];     // +0x04
    float tZ = to[2];     // +0x08
    float tW = to[3];     // +0x0C (w of 'to', computed but not used)

    // Compute linear interpolation for x, y, z: result = mix * from + to
    this->x = mix * from[0] + to[0]; // +0x00
    this->y = mix * from[1] + to[1]; // +0x04
    this->z = mix * from[2] + to[2]; // +0x08

    // The w component would be set to mix*from.w + to.w, but then immediately overwritten with original w.
    // This indicates the w should remain unchanged (e.g., preserving a rotation or weight).
    this->w = originalW; // +0x0C
}