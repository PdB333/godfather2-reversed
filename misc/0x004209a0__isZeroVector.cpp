// FUNC_NAME: isZeroVector
bool __fastcall isZeroVector(const int* vec)
{
    // Check if all four int components (e.g., x, y, z, w) are zero.
    // Used to test for null vectors or identity quaternions.
    if (vec[0] == 0 && vec[1] == 0 && vec[2] == 0 && vec[3] == 0)
    {
        return true;
    }
    return false;
}