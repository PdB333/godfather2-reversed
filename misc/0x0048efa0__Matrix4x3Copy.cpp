// FUNC_NAME: Matrix4x3Copy
void Matrix4x3Copy(float* dst, float* src)
{
    // Copy 12 floats (3x4 matrix) from src to dst
    for (int i = 0; i < 12; i++)
    {
        dst[i] = src[i];
    }
}