// FUNC_NAME: Matrix3::clear
void __fastcall Matrix3::clear(float matrix[3][3])
// Sets all 9 elements of a 3x3 matrix to 0.0f (identity translation/scale cleared)
// Address: 0x006b8040
{
    matrix[0][0] = 0.0f;
    matrix[0][1] = 0.0f;
    matrix[0][2] = 0.0f;
    matrix[1][0] = 0.0f;
    matrix[1][1] = 0.0f;
    matrix[1][2] = 0.0f;
    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = 0.0f;
}