// FUNC_NAME: Vector4::scaleAdd
void __fastcall Vector4::scaleAdd(float *this, const float *a, const float *b, float t)
{
    // Performs: this->xyz = t * a.xyz + b.xyz, while preserving the original w component
    // This is a vector scale-and-add operation, typically used for blending positions or directions
    // while leaving the homogeneous coordinate (w) untouched.

    // Save original w before overwriting
    float originalW = this[3];

    // Compute interpolated components
    this[0] = t * a[0] + b[0];   // x
    this[1] = t * a[1] + b[1];   // y
    this[2] = t * a[2] + b[2];   // z
    this[3] = t * a[3] + b[3];   // w (temporary, will be reverted)

    // Restore the original w component
    this[3] = originalW;
}