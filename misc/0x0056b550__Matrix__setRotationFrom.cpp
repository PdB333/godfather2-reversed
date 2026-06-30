// FUNC_NAME: Matrix::setRotationFrom
void __fastcall Matrix::setRotationFrom(const Matrix &other)
{
    // Copy orientation and scale from 'other', but preserve translation components (indices 3, 7, 11)
    // Destination matrix is this (in ECX), source is other (in EDX)
    // Assumes row-major 4x3 affine matrix (12 floats): 
    //   [0][1][2][3]  (rotation + translation X)
    //   [4][5][6][7]  (rotation + translation Y)
    //   [8][9][10][11] (rotation + translation Z)
    // Indices 3,7,11 are the translation vector.

    float preservedTx = m[3];
    float preservedTy = m[7];
    float preservedTz = m[11];

    m[0] = other.m[0];
    m[1] = other.m[4];
    m[2] = other.m[8];
    m[3] = other.m[3];   // will be overwritten
    m[4] = other.m[1];
    m[5] = other.m[5];
    m[6] = other.m[9];
    m[7] = other.m[7];   // will be overwritten
    m[8] = other.m[2];
    m[9] = other.m[6];
    m[10] = other.m[10];
    m[11] = other.m[11]; // will be overwritten

    // Restore original translation
    m[3] = preservedTx;
    m[7] = preservedTy;
    m[11] = preservedTz;
}