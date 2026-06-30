// FUNC_NAME: Vector3::scale

// Function address: 0x00582960
// This is a member function of a Vector3 class (with a fourth component, likely for alignment or homogeneous coordinates).
// It scales the x, y, z components of the object by the given factor,
// using the components of the input vector 'src' as the source values,
// while preserving the original w component of the object.
// Note: The scaling is applied to src's w temporarily, but then overwritten with the original w.

void __thiscall Vector3::scale(float *this, float *src, float scale)
{
    float srcY = src[1];
    float srcZ = src[2];
    float srcW = src[3];
    float originalW = this[3];

    this[0] = scale * src[0];
    this[1] = scale * srcY;
    this[2] = scale * srcZ;
    this[3] = scale * srcW;  // Temporary write, overwritten next line
    this[3] = originalW;     // Preserve original w component
}