// FUNC_NAME: CMatrix4::setWithChangeCheck
// 0x004166b0 - Set matrix from another 4x4 matrix (16 floats) and return whether it changed.
// This is a __fastcall member function with this in ECX and param1 (const float* source) in EDX.
bool __fastcall CMatrix4::setWithChangeCheck(const float* source)
{
    float old[16];
    // Save all 16 floats before overwriting
    old[0] = m[0];
    old[1] = m[1];
    old[2] = m[2];
    old[3] = m[3];
    old[4] = m[4];
    old[5] = m[5];
    old[6] = m[6];
    old[7] = m[7];
    old[8] = m[8];
    old[9] = m[9];
    old[10] = m[10];
    old[11] = m[11];
    old[12] = m[12];
    old[13] = m[13];
    old[14] = m[14];
    old[15] = m[15];

    // Copy new values from source
    m[0] = source[0];
    m[1] = source[1];
    m[2] = source[2];
    m[3] = source[3];
    m[4] = source[4];
    m[5] = source[5];
    m[6] = source[6];
    m[7] = source[7];
    m[8] = source[8];
    m[9] = source[9];
    m[10] = source[10];
    m[11] = source[11];
    m[12] = source[12];
    m[13] = source[13];
    m[14] = source[14];
    m[15] = source[15];

    // Compare old vs new values; return true if any element differs
    if (old[0] != m[0] || old[1] != m[1] || old[2] != m[2] || old[3] != m[3] ||
        old[4] != m[4] || old[5] != m[5] || old[6] != m[6] || old[7] != m[7] ||
        old[8] != m[8] || old[9] != m[9] || old[10] != m[10] || old[11] != m[11] ||
        old[12] != m[12] || old[13] != m[13] || old[14] != m[14] || old[15] != m[15])
    {
        return true;
    }
    return false;
}