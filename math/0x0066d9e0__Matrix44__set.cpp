// FUNC_NAME: Matrix44::set
bool __thiscall Matrix44::set(Matrix44 *this, const float src[16])
{
    float oldVals[16];
    int i;

    // Save old matrix values
    for (i = 0; i < 16; i++)
        oldVals[i] = this->m[i];

    // Copy new matrix from source
    for (i = 0; i < 16; i++)
        this->m[i] = src[i];

    // Check if any value changed
    for (i = 0; i < 16; i++)
    {
        if (this->m[i] != oldVals[i])
            return true;
    }
    return false;
}