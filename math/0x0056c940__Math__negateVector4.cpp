// FUNC_NAME: Math::negateVector4
void __fastcall Math::negateVector4(float *result, const float *source)
{
    // Negate each component of a 4D vector
    result[0] = -source[0];
    result[1] = -source[1];
    result[2] = -source[2];
    result[3] = -source[3];
}