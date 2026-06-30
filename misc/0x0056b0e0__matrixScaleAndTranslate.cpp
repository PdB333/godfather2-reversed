// FUNC_NAME: matrixScaleAndTranslate
void matrixScaleAndTranslate(float* inMatrix, float* outMatrix, float* scaleFactors)
{
    float m30, m31, m32, m33; // last row of input matrix
    float m00, m01, m02;      // first row (x)
    float m10, m11, m12;      // second row (y)
    float m20, m21, m22;      // third row (z)
    float sx2, sy2, sz2;      // squared scale factors

    m30 = inMatrix[0xc];
    m31 = inMatrix[0xd];
    m32 = inMatrix[0xe];
    m33 = inMatrix[0xf];

    m00 = inMatrix[0];
    m01 = inMatrix[1];
    m02 = inMatrix[2];

    m10 = inMatrix[4];
    m11 = inMatrix[5];
    m12 = inMatrix[6];

    m20 = inMatrix[8];
    m21 = inMatrix[9];
    m22 = inMatrix[10];

    sx2 = scaleFactors[0] * scaleFactors[0];
    sy2 = scaleFactors[1] * scaleFactors[1];
    sz2 = scaleFactors[2] * scaleFactors[2];

    // Scale the 3x3 rotation/scale part: columns are scaled by squared factors
    // Column 0 scaled by sx2, column1 by sy2, column2 by sz2
    outMatrix[0]  = sx2 * m00;
    outMatrix[1]  = sy2 * m10;
    outMatrix[2]  = sz2 * m20;
    outMatrix[3]  = 0.0f; // last element of row0

    outMatrix[4]  = sx2 * m01;
    outMatrix[5]  = sy2 * m11;
    outMatrix[6]  = sz2 * m21;
    outMatrix[7]  = 0.0f; // row1 last element

    outMatrix[8]  = sx2 * m02;
    outMatrix[9]  = sy2 * m12;
    outMatrix[10] = sz2 * m22;
    outMatrix[11] = 0.0f; // row2 last element

    // Compute new translation row: -(scaled dot product of translation with each column)
    // The original translation part (m30,m31,m32) is replaced by - (sx2*(m30*m00+m31*m01+m32*m02) etc.)
    outMatrix[0xc] = - (sx2 * (m30*m00 + m31*m01 + m32*m02));
    outMatrix[0xd] = - (sy2 * (m30*m10 + m31*m11 + m32*m12));
    outMatrix[0xe] = - (sz2 * (m30*m20 + m31*m21 + m32*m22));

    // Set homogeneous component to a global constant (likely 1.0f)
    outMatrix[0xf] = DAT_00e2b1a4; // +0x0f constant from data section
}