// FUNC_NAME: MathUtils::swapAndCopyVector4
void MathUtils::swapAndCopyVector4(float* source, float* dest)
{
    // Copy first 4 components from source to dest, then overwrite dest[3] with source[3]
    // This is essentially a vector4 copy with a redundant final assignment
    float x = source[0];
    float y = source[1];
    float z = source[2];
    float w = source[3];
    
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    dest[3] = w;
    dest[3] = source[3]; // Redundant, but preserves original behavior
}